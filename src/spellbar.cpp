#include "spellbar.h"

MSpellbar::MSpellbar() 
    : bg(new MSprite("pics/spellbar.png"))
    , CurrentSpell(-1)
{
    X = Gmachine->getWidth()/2-210;
    Y = Gmachine->getHeight()-35;
    bg->setRect(X,Y,420,35);
    bg->alfa = 128;
    for(int i=0; i<12; i++) actions[i] = NULL;
    for(int i=0; i<10; i++) Keys[i] = i+'0';
    Keys[10] = KEY_LBUTTON;
    Keys[11] = KEY_RBUTTON;
}

MSpellbar::~MSpellbar() {
}

void MSpellbar::draw() {
    bg->draw();
    for(int i=0; i<12; i++) {
        if(actions[i]!=NULL) {
            actions[i]->icon->setRect(X+33*i+1,Y+1,32,32);
            if(CurrentSpell==i) actions[i]->icon->setFocus(true);
            else actions[i]->icon->setFocus(false);
            actions[i]->icon->draw();
        }
    }
    MDrawableContainer::draw();
}

void MSpellbar::addAction(MAction* m, int pos) {
    if(pos>=12 || pos<0) return;
    if(actions[pos]!=NULL) actions[pos]->icon->setVisible(false);
    actions[pos] = m;
    m->icon->setRect(X+33*pos+1,Y+1,32,32);
    m->icon->setVisible(true);
    printf("action added!\n");
}


MAction* MSpellbar::getAction() {
    if(CurrentSpell>=0) return NULL;
    for(int i=0; i<12; i++) {
        if(Gkeyboard->IsKeyDown(Keys[i])) {
            CurrentSpell=i;
            return actions[i];
        }
    }
    return NULL;
}

void MSpellbar::SpellEnd() {
    CurrentSpell = -1;
}
