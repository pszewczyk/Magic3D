#ifndef MMORTAL_H
#define MMORTAL_H

#include <queue>

#include "target.h"
#include "mesh.h"
#include "primitives.h"
#include "camera.h"
#include "interface.h"
#include "action.h"
#include "config.h"
#include "inventory.h"

class MMortal : public MTarget {
protected:
    std::map<std::string, int> stats;
    std::vector<MAction*> skills;
    MInventory* inventory;
    
    int lefttogo;
    int ActionTime;
    MTarget* target;
    MSpeak* speak;
    std::string action;
    MAction* CurrentAction;
public:
    std::vector<MTarget*> around;    //targety znajduj¹ce siê w pobli¿u
    bool agressive;
    bool dead;
    bool busy;
    bool locked;
    MMortal(CDefsTable* defs);
    ~MMortal();
    void TurnLeft(float);
    void TurnRight(float);
    void setRotation(float);
    void MoveForward(float);
    void MoveLeft(float);
    void MoveRight(float);
    void MoveBackward(float);
    virtual bool learnSkill(MAction* m);
    void useAction(MAction*);
    void FinishAction();
    void hit(std::map<std::string, int> adds);
    void setTarget(MTarget* target);
    void setBusy(int);
    void WaitForAction(int);
    void checkLife();
    virtual void update();
    void grab(MItem*);
    void updateItem(MItem*);
    void ClearAll();
    MSprite* createLabel();
    std::vector<MItem*> getItems();
    
    void say(std::string);
    void shutUp();
    
    virtual std::string act() = 0;
    void die();
};

#endif
