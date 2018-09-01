#ifndef M_DRAWABLE_CONTAINER
#define M_DRAWABLE_CONTAINER

#include "interface.h"
#include <vector>

class MDrawableContainer : public MDrawable {
protected:
    map<string, MDrawable*> drawables;
public:
    MDrawableContainer();
    void addDrawable(string, MDrawable*);
    void rmDrawable(string);
    virtual void draw();
};

class MLinkedContainer : public MDrawableContainer {
private:
    Mvector3d* center;
    Mvector3d radius;
public:
    MLinkedContainer();
    ~MLinkedContainer();
    void setRadius(Mvector3d);
    void linkPos(Mvector3d*);
    virtual void draw();
};

#endif
