#include "npc.h"

MNpc::MNpc(CDefsTable* defs)
    : MMortal(defs)
    , talk(new MTalk(defs->GetTable("talk")))
    , hpbar(new MBar(stats["hp"], "pics/bars/redbar.png"))
{
    hpbar->setRect(0,0,100,10);
    hpbar->setVisible(true);
    label->addDrawable("hpbar",(MDrawable*)hpbar);
    label->setRadius (Mvector3d (0, 1.2*MSCALE, 0));
    Gmachine->addDrawable ((MDrawable*) label);
    label->setVisible(false);
}

MNpc::~MNpc() {
    delete talk;
    delete hpbar;
}

MTalk* MNpc::getTalk() {
    return talk;
}

MItem* MNpc::getGift() {
    if(talk->getGiftString()=="nothing") return NULL;
    CDefsTable* defs = new CDefsTable(talk->getGiftString());
    MItem* item = new MItem(defs);
    printf("%s gives you %s\n", name.c_str(), item->getType().c_str());
    delete defs;
    return item;
}

MAction* MNpc::getKnowlege() {
    if(talk->getKnowlegeString()=="nothing") return NULL;
    CDefsTable* defs = new CDefsTable(talk->getKnowlegeString());
    MAction* action = new MAction(defs);
    printf("%s teaches you\n", name.c_str());
    delete defs;
    return action;
}

string MNpc::act() {
    if(dead) return "dead";
    say(talk->getInvitation());
    return "talk";
}

void MNpc::onSpace() {
    shutUp();
    say(talk->getCurrentAnswer());
}

void MNpc::update() {
    hpbar->setValue(stats["hp"]);
    MMortal::update();
}

bool MNpc::learnSkill(MAction* m) {
    return MMortal::learnSkill(m);
}
