#ifndef MITEM_H
#define MITEM_H

#include "mesh.h"
#include "target.h"
#include "icon.h"
#include "defstable.h"
#include "config.h"

class MItem : public MTarget {
public:
    std::map<std::string, int> adds;
    std::string type;
    bool equiped;
    MIcon* icon;
    MItem(CDefsTable*);
    ~MItem();
    std::string act();
    //void updateOwner(MMortal* m);
    std::string getType();
    void setEquiped(bool);
};


#endif
