#ifndef MMINIMAP_H
#define MMINIMAP_H

#include <irrlicht.h>
#include <vector>

#include "drawable.h"
#include "globalcrap.h"
#include "config.h"

class MMinimap : public MDrawable {
protected:
    ITexture* Tex;
    int X,Y,W,H;
    int Xpos, Ypos, Xsize, Ysize;
    int s;
public:
    MMinimap(vector<vector<bool> > mapa);
    ~MMinimap();
    void draw();
    void updatePos(int,int);
};

#endif
