#include "item.h"

MItem::MItem(CDefsTable* defs)
    : MTarget(defs->GetString("name", "noname item"))
    , type(defs->GetString("type", "other"))
    , icon(new MIcon(defs->GetString("icon")))
    , equiped(false)
{
    adds = defs->GetIntMap("adds");
    loadModel(defs->GetString("model","nomodel"));
    setAnim(0,0);
    printf("Item created!");
}

MItem::~MItem() 
{
}

string MItem::act() {
    return "take";
}

/*void MItem::updateOwner(MMortal* m) {
    x = m->x;
    y = m->y;
    z = m->z;
    rot = m->getRot();
    setAnim(m->getStartFrame(),m->getEndFrame());
    update_pos();
}*/

string MItem::getType() {
    return type;
}

void MItem::setEquiped(bool e) {
    equiped = e;
    if(e) {
        icon->setCheck();
        node->setVisible(true);
        setSelectable(false);
    }
    else {
        icon->setNormal();
        node->setVisible(false);
        setSelectable(true);
    }
}
