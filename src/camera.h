#ifndef MCAMERA_H
#define MCAMERA_H

#include <irrlicht.h>
#include <vector>
#include <string>
#include <fstream>

#include "primitives.h"
#include "config.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

class MCamera : public Mvector3d {
private:
    ICameraSceneNode* node;
    Mvector3d* lookat;
    bool locked;
    Mvector3d radius;
public:
    MCamera();
    MCamera(Mvector3d);
    ~MCamera();
    void update();
    void lookAt(Mvector3d);
    void linkManager(ISceneManager*);
    void linkTarget(Mvector3d*);
    void translate(Mvector3d); //translacja
    void setRadius(Mvector3d);
    void setDistance(double);
    void addDistance(double);
};

#endif
