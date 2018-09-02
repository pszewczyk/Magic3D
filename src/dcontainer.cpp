#include "dcontainer.h"

MDrawableContainer::MDrawableContainer() 
{
}

void MDrawableContainer::addDrawable(std::string name, MDrawable* d) {
    printf("adding drawable: %s\n", name.c_str());
    drawables[name] = d;
}

void MDrawableContainer::rmDrawable(std::string name) {
    drawables.erase(name);
}

void MDrawableContainer::draw() {
    for(std::map<std::string, MDrawable*>::iterator it = drawables.begin(); it!=drawables.end(); it++)
        it->second->draw();
}

MLinkedContainer::MLinkedContainer()
    : MDrawableContainer()
{
}

MLinkedContainer::~MLinkedContainer() {
}

void MLinkedContainer::draw() {
    position2d <s32> p = Gmachine->getManager()->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition (
                    vector3df (center->x + radius.x, center->y + radius.y, center->z + radius.z));
    X = p.X-Width/2;
    Y = p.Y;
    for(std::map<std::string, MDrawable*>::iterator it = drawables.begin(); it!=drawables.end(); it++)
        it->second->Translate(X,Y);
        
    MDrawableContainer::draw();
    
    for(std::map<std::string, MDrawable*>::iterator it = drawables.begin(); it!=drawables.end(); it++)
        it->second->Translate(-X,-Y);
}

void MLinkedContainer::setRadius(Mvector3d m) {
    radius = m;
}

void MLinkedContainer::linkPos(Mvector3d* m) {
    center = m;
}
