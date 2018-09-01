#include "camera.h"

MCamera::MCamera()
	: Mvector3d(MSCALE, MSCALE, MSCALE)
	, node(0)
	, lookat(new Mvector3d(0,0,0)) //wypadaloby delete tego?
	, locked(1)
	, radius()
{
}

MCamera::MCamera(Mvector3d a)
	: Mvector3d(a)
	, node(0)
	, lookat(new Mvector3d(0,0,0)) //wypadaloby delete tego?
	, locked(0)
	, radius()
{
}

MCamera::~MCamera() {
    delete lookat;
}

void MCamera::update() {
    if(radius.length() < MSCALE / 100) radius = radius*10;
    if(locked) {
        x = lookat->x + radius.x;
        y = lookat->y + radius.y;
        z = lookat->z + radius.z;
    }
    setDistance(radius.length());
    node->setPosition(vector3df(x,y,z));
    node->setTarget(vector3df(lookat->x, lookat->y, lookat->z));
}

void MCamera::linkManager(ISceneManager* manager) {
    node = manager->addCameraSceneNode(0, vector3df(x,y,z), vector3df(lookat->x, lookat->y, lookat->z));
}

void MCamera::linkTarget(Mvector3d* l) {
    lookat = l;
    locked = true;
    radius = Mvector3d(x - lookat->x, y - lookat->y, z - lookat->z);
}

void MCamera::translate(Mvector3d a) {
    if(locked) {
        float nx = (radius.x * cos(a.x * 3.14 / 180)) - (radius.z * sin(a.x * 3.14 / 180));
        float nz = (radius.x * sin(a.x * 3.14 / 180)) + (radius.z * cos(a.x * 3.14 / 180));
        float ny = radius.y + a.y;
        if(ny < (MSCALE / 100)) ny = MSCALE / 100;
        radius = Mvector3d(nx,ny,nz);
    }
    else {
        x += a.x;
        y += a.y;
        z += a.z;
    }
}

void MCamera::setRadius(Mvector3d a) {
    a = a.normalize();
    double length2d = sqrt(radius.x*radius.x+radius.z*radius.z);
    if(locked) {
        radius = Mvector3d(a.x*length2d,radius.y,a.z*length2d);
        //radius = a*radius.length();
    }
}


void MCamera::setDistance(double d) {
    if(d>MALLOWED_DISTANCE) d = MALLOWED_DISTANCE;
    radius = radius.normalize();
    radius = radius*d;
}

void MCamera::addDistance(double d) {
    setDistance(radius.length()+d);
}
