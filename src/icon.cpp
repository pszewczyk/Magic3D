#include "icon.h"

MIcon::MIcon() 
{
}

MIcon::MIcon(std::string filename)
    : MSprite(filename)
    , check(false)
{
    setRect(0,0,64,64);
    a=r=g=b=255;
}

void MIcon::setCheck() {
    a=r=g=b=255;
    check = true;
}

void MIcon::setNormal() {
    a=r=g=b=200;
    check = false;
}

void MIcon::setFocus(bool t) {
    if(t) {
        a=g=b=128;
        r=255;
    }
    else if(check) setCheck();
    else setNormal();
}

void MIcon::draw() {
    Gmachine->getDriver()->draw2DImage
        ( texture, 
        position2d <s32> (X,Y), 
        rect <s32> (0, 0, Width, Height), 
        0, 
        SColor(a, r, g, b), 
        true );
}

bool MIcon::hover(int xPos, int yPos) {
    return xPos>=X && yPos>=Y && xPos<=X+Width && yPos<=Y+Height;
}
