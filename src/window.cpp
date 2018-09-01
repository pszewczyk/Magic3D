#include "window.h"

MWindow::MWindow()
    : bg(new MSprite("pics/screen.png"))
    , ContextMenu(NULL)
{
    X = Gmachine->getWidth()/2-350;
    Width = 700;
    Y = Gmachine->getHeight()/2-250;
    Height = 500;
    bg->setRect(X,Y,Width,Height);
}

void MWindow::draw() {
    bg->draw();
    MDrawableContainer::draw();
    if(ContextMenu) ContextMenu->draw();
}
