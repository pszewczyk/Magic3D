#ifndef MWINDOW_H
#define MWINDOW_H

#include "menu.h"
#include "dcontainer.h"
#include "interface.h"

class MWindow : public MDrawableContainer {
protected:
    MSprite* bg;
    MMenu* ContextMenu;
public:
    int left, right, up, bottom;
    MWindow();
    virtual void draw();
    virtual string onClick() = 0;
    virtual void showCMenu() = 0;
};

#endif
