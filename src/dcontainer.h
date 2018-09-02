#ifndef M_DRAWABLE_CONTAINER
#define M_DRAWABLE_CONTAINER

#include "interface.h"
#include <vector>

class MDrawableContainer : public MDrawable {
protected:
    std::map<std::string, MDrawable*> drawables;
public:
    MDrawableContainer();
    void addDrawable(std::string, MDrawable*);
    void rmDrawable(std::string);
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
