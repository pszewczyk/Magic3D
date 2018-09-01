#ifndef TARGET_H
#define TARGET_H

#include <queue>

#include "mesh.h"
#include "primitives.h"
#include "camera.h"
#include "interface.h"
#include "dcontainer.h"
#include "action.h"
#include "config.h"

class MTarget : public MAnimatedMesh {
protected:
    MLinkedContainer* label;
public:
    string name;
    string id;
    bool selectable;
    bool isFocus;
    bool destroyable;
    MTarget(string);
    ~MTarget();
    void Focus();
    void unFocus();
    void setSelectable(bool);
    void show(bool);
    
    virtual string act() = 0;
};

#endif
