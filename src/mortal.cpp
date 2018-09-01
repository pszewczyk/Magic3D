#include "mortal.h"

MMortal::MMortal(CDefsTable* defs)
	: MTarget(defs->GetString("name", "default stickman"))
	, busy(false)
	, target(NULL)
	, action("born")
	, speak(new MSpeak("co?",(Mvector3d*)this))
	, inventory(new MInventory(defs->GetTable("inventory")))
	, agressive(false)
	, dead(false)
	, lefttogo(0)
	, locked(false)
	, ActionTime(-1)
	, CurrentAction(NULL)
{
    speak->setVisible(false);
    Gmachine->addDrawable((MDrawable*)speak);
    loadModel(defs->GetString("model"));
    
    //statystyki:
    CDefsTable* sd = defs->GetTable("stats");
    stats["maxhp"] = defs->GetInt("maxhp", 100);
    stats["hp"] = stats["maxhp"];
    stats["maxmp"] = defs->GetInt("maxmp", 100);
    stats["mp"] = stats["maxmp"];
    destroyable = true;
}

void MMortal::checkLife() {
    //if(stats["hp"]>stats["maxhp"]) stats["hp"] = stats["maxhp"];
    if(stats["hp"]<=0) die();
}

MMortal::~MMortal(){
    ClearAll();
}

void MMortal::TurnLeft(float angle) {
    if(busy) return;
    rotate(Mvector3d(0.0, -angle, 0.0));
    action = "turning_left";
}
void MMortal::TurnRight(float angle) {
    if(busy) return;
    rotate(Mvector3d(0.0, angle, 0.0));
    action = "turning_right";
}

void MMortal::setRotation(float angle) {
    //TODO
}

void MMortal::MoveLeft(float dist) {
    if(busy) return;
    localTrans(Mvector3d(-dist, 0.0, 0.0));
    setAnim("run");
    action = "running_left";
}

void MMortal::MoveRight(float dist) {
    if(busy) return;
    localTrans(Mvector3d(dist, 0.0, 0.0));
    setAnim("run");
    action = "running_right";
}

void MMortal::MoveForward(float dist) {
    if(busy) return;
    localTrans(Mvector3d(0.0, 0.0, dist));
    setAnim("run");
    action = "running_forward";
}
void MMortal::MoveBackward(float dist) {
    if(busy) return;
    localTrans(Mvector3d(0.0, 0.0, -dist));
    setAnim("run");
    action = "moving_backward";
}

bool MMortal::learnSkill(MAction* m) {
    for(int i=0; i<skills.size(); i++)
        if(skills[i]->name == m->name) {
            printf("you already know this spell\n");
            return false;
        }
    skills.push_back(m);
    return true;
}

void MMortal::useAction(MAction* a) {
    if(dead) return;    
    printf("trying to hit sb\n");
    action = "hit";
    if(skills.size()==0) {
        printf("u have no skill!\n");
        return;
    }
    setAnim(a->anim);
    setBusy(a->castingTime);
    WaitForAction(a->duration);
    CurrentAction = a;
}

void MMortal::FinishAction() {
    if(target==NULL || (sqrt((target->x-x)*(target->x-x) + (target->z-z)*(target->z-z))>skills[0]->dist && skills[0]->dist!=0)) {
        printf("pudlo!\n");
        return;
    }
    printf("using default (%s) action on mortal target\n", skills[0]->name.c_str());
    ((MMortal*)target)->hit(CurrentAction->effects);
    ActionTime = -1;
}

void MMortal::WaitForAction(int a) {
    ActionTime = a;
}

void MMortal::setTarget(MTarget* t) {
    target = t;
}

void MMortal::hit(map<string, int> adds) {
    if(dead) return;
    printf("%s: aua! (%d effects)\n", name.c_str(), adds.size());
    for(map<string,int>::iterator it = stats.begin(); it!=stats.end(); it++) {
        if(adds.find(it->first)!=adds.end()) printf("%s += %d\n", it->first.c_str(), adds[it->first]);
        it->second += adds[it->first];
    }
}

void MMortal::grab(MItem* a) {
    printf("grabbing some equipement...\n");
    inventory->grab(a);
}

MSprite* MMortal::createLabel() {
    /*TODO*/
}

vector<MItem*> MMortal::getItems() {
    return inventory->slots;
}

void MMortal::say(string s) {
    //if(speak) delete speak;
    speak->setVisible(true);
    speak->setText(s);
    //speak = new MSpeak(s,(Mvector3d*)this);
}

void MMortal::shutUp() {
    //if(speak) delete speak;
    Gmachine->checkEr();
    speak->setVisible(false);
}

void MMortal::setBusy(int a) {
    busy = lefttogo = a;
    //action = "nothing";
}

void MMortal::updateItem(MItem* a) {
    if(a==NULL) return;
    if(dead) {
        inventory->ThrowOut(a);
        return;
    }
    a->x = x;
    a->y = y;
    a->z = z;
    a->setRot(getRot());
    a->setAnim(getStartFrame(),getEndFrame());
    a->update_pos();
}

void MMortal::update() {
    //printf("updating %s... ", name.c_str());
    //if(!target && action=="talking") setBusy(false);
    
    checkLife();
    
    //magia - czekanie do koñca animacji
    if(!locked && node->getEndFrame()-node->getFrameNr()<2) busy=false;
    if(ActionTime==0) {
        FinishAction();
        ActionTime = -1;
    }
    else ActionTime--;

    
    
    if(!isFocus) shutUp();
    update_pos();
    inventory->updatePos(x,y,z);
    updateItem(inventory->getEquiped("head"));
    updateItem(inventory->getEquiped("torso"));
    updateItem(inventory->getEquiped("legs"));
    updateItem(inventory->getEquiped("arms"));
    updateItem(inventory->getEquiped("hands"));
    updateItem(inventory->getEquiped("foots"));
    
    inventory->highlight(isFocus);
    
    //printf("updated\n");
}

void MMortal::ClearAll() {
    skills.clear();
    stats.clear();
    //delete inventory;
    shutUp();
}

void MMortal::die() {
    if(dead) return;
    printf("next soul to the hell\n");
    shutUp();
    dead = true;
    setAnim("die");
    node->setLoopMode(false);
    rotate(Mvector3d(0.0, 1.0*Gmachine->random(360), 0.0));
    setSelectable(false);
}
