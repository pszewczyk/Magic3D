#ifndef MINVENTORY_H
#define MINVENTORY_H

#include "item.h"
#include "menu.h"
#include "defstable.h"
#include "window.h"

class MInventory : public MWindow {
private:
    std::map<std::string, MItem*> equiped;
    bool eqble(MItem*);
    bool eatable(MItem*);
    MItem* ContextItem;
public:
    std::vector<MItem*> slots;
    MInventory();
    MInventory(CDefsTable*);
    bool grab(MItem*);
    bool equip(MItem*);
    bool unequip(MItem*);
    bool ThrowOut(int);
    bool ThrowOut(MItem*);
    MItem* getEquiped(std::string);
    virtual void draw();
    std::string onClick();
    void showCMenu();
    void highlight(bool);
    void updatePos(double,double,double);
    MItem* getContextItem();
};

#endif
