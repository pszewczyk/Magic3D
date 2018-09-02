#include "minimap.h"

MMinimap::MMinimap(std::vector<std::vector<bool> > mapa) 
    : MDrawable()
{
    s = 10;
    IImage* image = Gmachine->driver->createImage(ECF_A1R5G5B5, dimension2d<u32>(mapa.size()*s, mapa[0].size()*s));
    Xsize = mapa.size()*s;
    Ysize = mapa[0].size()*s;
    for(int i=0; i<mapa.size(); i++) {
        for(int j=0; j<mapa[i].size(); j++) { 
            for(int x=s*i; x<s*(i+1); x++) for(int y=s*j; y<s*(j+1); y++){
                if(mapa[i][j]) image->setPixel(x,mapa[i].size()*s-y,SColor(255,255,255,255));
                else image->setPixel(x,mapa[i].size()*s-y,SColor(255,128,128,128));
            }
        }
    }
    Tex = Gmachine->driver->addTexture("tmp/minimap.png",image);
    W = H = 100;
    X = 0;
    Y = Gmachine->getHeight()-H;
    Xpos = Ypos = 0;
}

MMinimap::~MMinimap() {
}

void MMinimap::draw() {
    int x,y;
    if(2*Xpos<W) x=0;
    else x = Xpos-W/2;
    if(2*Ypos<H) y=0;
    else y = Ypos-H/2;
    Gmachine->getDriver()->draw2DImage(Tex, position2d <s32> (X,Y), rect <s32> (x, y, x+W, y+H), 0, SColor(255, 255, 255, 255), true);
}


void MMinimap::updatePos(int x, int y) {
    Xpos = x*s;
    Ypos = y*s;
    Ypos = Ysize - Ypos;
}
