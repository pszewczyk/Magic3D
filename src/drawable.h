#ifndef MDRAWABLE_H
#define MDRAWABLE_H

#include <irrlicht.h>
#include <stdio.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//drawable, czyli coœ co mo¿na narysowaæ
class MDrawable {
protected:
    bool Visible;
    int X, Y, Width, Height;
public:
    MDrawable();
    ~MDrawable();
    void setVisible(bool visible);
    bool getVisible();
    virtual void draw() = 0;
    void setPos(int,int);
    void setRect(int, int, int, int);
    void Translate(int, int);
};

#endif
