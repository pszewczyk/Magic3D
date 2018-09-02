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
    std::string name;
    std::string id;
    bool selectable;
    bool isFocus;
    bool destroyable;
    MTarget(std::string);
    ~MTarget();
    void Focus();
    void unFocus();
    void setSelectable(bool);
    void show(bool);
    
    virtual std::string act() = 0;
};

#endif
