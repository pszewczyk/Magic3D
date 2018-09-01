#ifndef MICON_H
#define MICON_H

#include "interface.h"

class MIcon : public MSprite {
private:
    int a, r, g, b;
    bool check;
public:
    MIcon();
    MIcon(string);
    
    bool hover(int, int);
    
    void setCheck();
    void setFocus(bool);
    void setNormal();
    
    void draw();
};

#endif
