#include "player.h"

MPlayer::MPlayer(CDefsTable* defs)
    : MMortal(defs)
    , hpbar(new MBar(stats["hp"], "pics/bars/redbar.png"))
    , mpbar(new MBar(stats["mp"], "pics/bars/bluebar.png"))
    , spellscreen(new MSpellScreen())
    , spellbar(new MSpellbar())
{
    hpbar->setRect(1,1,100,10);
    mpbar->setRect(1,11,100,10);
}

MPlayer::~MPlayer() {
    hpbar->setVisible(false);
    mpbar->setVisible(false);
}

bool MPlayer::isTalking() {
    return action=="talking";
}

string MPlayer::act() {
    return "action playera";
}

void MPlayer::setTalking() {
    action="talking";
    setAnim("standing");
    busy = locked = true;
}

void MPlayer::endTalking() {
    action="nothing";
    busy = locked = false;
    lefttogo = 0;
}

void MPlayer::useItem(string s) {
    if(s=="eat") {
        printf("eating\n");
        MItem* food = inventory->getContextItem();
        for(map<string, int>::iterator it=food->adds.begin(); it!=food->adds.end(); it++) {
            stats[it->first] += it->second;
            printf("%s += %d\n", it->first.c_str(), it->second);
        }
    }
    updateBars();
    checkLife();
}

void MPlayer::updateBars() {
    hpbar->setValue(stats["hp"]);
    mpbar->setValue(stats["mp"]);
}

void MPlayer::update() {
    MMortal::update();
    updateBars();
    if(!busy) spellbar->SpellEnd();
    if(agressive) {
        MAction* coteraz = spellbar->getAction();
        if(coteraz!=NULL) useAction(coteraz);
    }
}

bool MPlayer::Control(int speed) {
        bool nth = true;
        bool slalom = (Gkeyboard->IsKeyDown('W')||Gkeyboard->IsKeyDown('S'))&&
                        (Gkeyboard->IsKeyDown('A')||Gkeyboard->IsKeyDown('D'));
        double movespeed = slalom ? speed*0.7 : speed;
        
        //ruszanie
        if(Gkeyboard->IsKeyDown('W')) {
            if(!Gkeyboard->IsKeyDown('S')) {
                MoveForward(movespeed);
                nth = false;
            }
        }
        else if(Gkeyboard->IsKeyDown('S')) {
            MoveBackward(movespeed);
            nth = false;
        }
        
        if(Gkeyboard->IsKeyDown('D')) {
            if(!Gkeyboard->IsKeyDown('A')) {    
                MoveRight(movespeed);
                nth = false;
            }
        }
        else if(Gkeyboard->IsKeyDown('A')) {
            MoveLeft(movespeed);
            nth = false;
        }
        
        if(Gkeyboard->IsKeyDown('Q') && !isTalking()) {
            agressive = !agressive;
            Gkeyboard->clear('Q');
        }
        
        if(nth && !busy) {
            if(agressive) setAnim("standing_alert");
            else setAnim("standing");
        }
        
        //klik myszo
        if(Gkeyboard->IsKeyDown(KEY_LBUTTON)) {
            if(!agressive && target && !isTalking()) {
                string act = target->act();
                if(act=="talk") setTalking();
                if(act=="take") grab((MItem*)target);
                Gkeyboard->clear(KEY_LBUTTON);
            }
        }
        
        //kulturalna rozmowa
        if(isTalking()) {
            MTalk* talk = ((MNpc*)target)->getTalk();
            if(Gkeyboard->IsKeyDown('W')) talk->up();
            Gkeyboard->clear('W');
            if(Gkeyboard->IsKeyDown('S')) talk->down();
            Gkeyboard->clear('S');
            if(Gkeyboard->IsKeyDown(' ')) {
                ((MNpc*)target)->onSpace();
                MItem* gift = ((MNpc*)target) -> getGift();
                MAction* knowlege = ((MNpc*)target) -> getKnowlege();
                if(gift!=NULL) {
                    // TODO:
                    //mapa->addTarget((MTarget*)gift);
                    grab(gift);
                }
                if(knowlege!=NULL) {
                    learnSkill(knowlege);
                }
                if(talk->end()) endTalking();
                Gkeyboard->clear(' ');
            }
        }
        
        return nth;
}

void MPlayer::pushToBar(int pos) {
    if(spellscreen->getContextAction()==NULL) return;
    spellbar->addAction(spellscreen->getContextAction(), pos);
}

MWindow* MPlayer::getInventoryScreen() {
    return (MWindow*)inventory;
}

MDrawable* MPlayer::genDrawableContainer() {
    MDrawableContainer* result = new MDrawableContainer();
    result->addDrawable("hpbar", hpbar);
    result->addDrawable("mpbar", mpbar);
    result->addDrawable("spellbar", spellbar);
    return (MDrawable*) result;
}

bool MPlayer::learnSkill(MAction* m) {
    if(MMortal::learnSkill(m))
        spellscreen->learn(m);
    return true;
}

MWindow* MPlayer::getSpellScreen() {
    return (MWindow*)spellscreen;
}
