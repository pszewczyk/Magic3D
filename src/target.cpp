#include "target.h"

MTarget::MTarget(string a)
    : MAnimatedMesh()
    , name(a)
    , label(new MLinkedContainer())
    , isFocus(false)
    , selectable(true)
    , destroyable(false)
{
    id = name;
    id.append("_");
    id.append(RandomString(6));
    MText* text = new MText(name);
    text -> setRect(0,20,500,500);
    label->addDrawable("label", (MDrawable*)(text));
    label->setRect(0,0,100,0);
    label->linkPos ((Mvector3d*)this);
    label->setRadius (Mvector3d (0, MSCALE, 0));
    Gmachine->addDrawable ((MDrawable*) label);
    label->setVisible(false);
}

MTarget::~MTarget() {
    delete label;
    //selectable = false;
}

void MTarget::Focus() {
    if(!selectable) return;
    setFocus(true);
    label->setVisible(true);
    isFocus = true;
}

void MTarget::unFocus() {
    setFocus(false);
    label->setVisible(false);
    isFocus = false;
}

void MTarget::setSelectable(bool Selectable) {
    selectable = Selectable;
}

void MTarget::show(bool b) {
    selectable = b;
    setVisible(b);
}
