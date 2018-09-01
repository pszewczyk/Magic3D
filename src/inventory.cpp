#include "inventory.h"

MInventory::MInventory() {
}

MInventory::MInventory(CDefsTable* defs)
{
    string names[6] = {"head","torso","legs","arms","hands","foots"};
    for(int i=0; i<6; i++)
        if(defs->GetString(names[i],"empty")!="empty") {
            MItem* a = new MItem(new CDefsTable(defs->GetString(names[i],"empty")));
            grab(a);
            equip(a);
        }
}

bool MInventory::eqble(MItem* b) {
    string a = b->type;
    return a=="head" || a=="torso" || a=="legs" || a=="arms" || a=="hands" || a=="foots";
}

bool MInventory::eatable(MItem* a) {
    return a->type=="potion";
}

bool MInventory::grab(MItem* a) {
    slots.push_back(a);
    addDrawable(a->id, a->icon);
    a->icon->setVisible(true);
    a->show(false);
    return true;
}

bool MInventory::equip(MItem* a) {
    if(!eqble(a)) return false;
    if(equiped[a->getType()]!=NULL) equiped[a->getType()]->setEquiped(false);
    equiped[a->getType()] = a;
    a->setEquiped(true);
    return true;
}

bool MInventory::unequip(MItem* a) {
    if(!a->equiped) return false;
    a->setEquiped(false);
    equiped[a->getType()] = NULL;
    a->setSelectable(false);
    return true;
}

bool MInventory::ThrowOut(int a) {
    if(slots[a]->equiped) unequip(slots[a]);
    slots[a]->show(true);
    slots[a]->setAnim("free");
    int di = Gmachine->random(360);
    slots[a]->x += 10*sin(di);
    slots[a]->z += 10*cos(di);
    slots[a]->rotate(Mvector3d(0.0, 1.0*Gmachine->random(360), 0.0));
    slots[a]->update_pos();
    rmDrawable(slots[a]->id);
    slots.erase(slots.begin()+a);
}

bool MInventory::ThrowOut(MItem* a) {    
    for(int i=0; i<slots.size(); i++) if(slots[i]==a)
        ThrowOut(i);
}

MItem* MInventory::getEquiped(string a) {
    if(equiped.find(a)==equiped.end()) return NULL;
    return equiped[a];
}

void MInventory::draw() {
    for(int i=0; i<slots.size(); i++) {
        int howmany = (Width)/65;
        slots[i]->icon->setRect(X+65*(i%howmany)+10,Y+(65*((i)/howmany))+10, 64, 64);
        if(!ContextMenu && slots[i]->icon->hover(Gmachine->getCursorX(), Gmachine->getCursorY())) slots[i]->icon->setFocus(true);
        else slots[i]->icon->setFocus(false);
    }
    MWindow::draw();
}

string MInventory::onClick() {
    if(ContextMenu) {
        if(ContextMenu->isDown("putoff")) {
            delete ContextMenu;
            ContextMenu = NULL;
            unequip(ContextItem);
            return "putoff";
        }
        else if(ContextMenu->isDown("puton")) {
            delete ContextMenu;
            ContextMenu = NULL;
            equip(ContextItem);
            return "puton";
        }
        else if(ContextMenu->isDown("throwout")) {
            delete ContextMenu;
            ContextMenu = NULL;
            ThrowOut(ContextItem);
            return "throwout";
        }
        else if(ContextMenu->isDown("eat")) {
            delete ContextMenu;
            ContextMenu = NULL;
            //delete slots[ContextItem];
            MItem* currentFood = ContextItem;
            ThrowOut(ContextItem);
            currentFood->show(false);
            return "eat";
        }
        delete ContextMenu;
        ContextMenu = NULL;
    }
    for(int i=0; i<slots.size(); i++) {
        if(slots[i]->icon->hover(Gmachine->getCursorX(), Gmachine->getCursorY())) {
            if(slots[i]->equiped) unequip(slots[i]);
            else equip(slots[i]);
        }
    }
    return "nothing";
}

void MInventory::showCMenu() {
    printf("showing cmenu..\n");
    ContextMenu = new MMenu("InventoryContextMenu", Gmachine->getCursorX(), Gmachine->getCursorY(), 150, 20); 
    for(int i=0; i<slots.size(); i++)
        if(slots[i]->icon->hover(Gmachine->getCursorX(), Gmachine->getCursorY())) {
            printf("making context menu\n");
            if(slots[i]->equiped) ContextMenu->addButton("putoff", "Zdejmij");
            else if(eqble(slots[i])) ContextMenu->addButton("puton", "Za³ó¿");
            if(eatable(slots[i])) ContextMenu->addButton("eat", "Spo¿yj");
            ContextMenu->addButton("throwout", "Wyrzuæ");
            ContextItem = slots[i];
            printf("%d item is context\n", ContextItem);
            return;
        }
}

void MInventory::highlight(bool b) {
    for(map<string, MItem*>::iterator it = equiped.begin(); it!=equiped.end(); it++)
        if(it->second!=NULL) {
            it->second->setFocus(b);
        }
}

void MInventory::updatePos(double x, double y, double z) {
    for(int i=0; i<slots.size(); i++) {
        slots[i]->x = x;
        slots[i]->y = y;
        slots[i]->z = z;
        slots[i]->update_pos();
    }
}

MItem* MInventory::getContextItem() {
    return ContextItem;
}
