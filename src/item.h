#ifndef MITEM_H
#define MITEM_H

#include "mesh.h"
#include "target.h"
#include "icon.h"
#include "defstable.h"
#include "config.h"

class MItem : public MTarget {
public:
    map<string, int> adds;
    string type;
    bool equiped;
    MIcon* icon;
    MItem(CDefsTable*);
    ~MItem();
    string act();
    //void updateOwner(MMortal* m);
    string getType();
    void setEquiped(bool);
};


#endif
