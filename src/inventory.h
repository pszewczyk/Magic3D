#ifndef MINVENTORY_H
#define MINVENTORY_H

#include "item.h"
#include "menu.h"
#include "defstable.h"
#include "window.h"

class MInventory : public MWindow {
private:
    map<string, MItem*> equiped;
    bool eqble(MItem*);
    bool eatable(MItem*);
    MItem* ContextItem;
public:
    vector<MItem*> slots;
    MInventory();
    MInventory(CDefsTable*);
    bool grab(MItem*);
    bool equip(MItem*);
    bool unequip(MItem*);
    bool ThrowOut(int);
    bool ThrowOut(MItem*);
    MItem* getEquiped(string);
    virtual void draw();
    string onClick();
    void showCMenu();
    void highlight(bool);
    void updatePos(double,double,double);
    MItem* getContextItem();
};

#endif
