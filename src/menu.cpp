#include "menu.h"

MMenu::MMenu(std::string t, int X, int Y)
    : title(t)
    , x(X)
    , y(Y)
    , width(200)
    , buttonHeight(30)
{
    printf("Menu '%s' created!\n", t.c_str());
}

MMenu::MMenu(std::string t, int X, int Y, int W, int H)
    : title(t)
    , x(X)
    , y(Y)
    , width(W)
    , buttonHeight(H)
{
    printf("Menu '%s' created!\n", t.c_str());
}

MMenu::~MMenu() {
    buttons.clear();
    setVisible(false);
    printf("Menu '%s' deleted\n", title.c_str());
}

void MMenu::addButton(MButton* b) {
    buttons.push_back(b);
    b->setRect(x,y+buttons.size()*buttonHeight,width,buttonHeight);
}

void MMenu::addButton(std::string id, std::string text) {
    MButton* b = new MButton(id, text);
    buttons.push_back(b);
    b->setRect(x,y+buttons.size()*buttonHeight,width,buttonHeight);
}

std::string MMenu::current() {
    for(int i=0; i<buttons.size(); i++)
        if(buttons[i]->hover(Gmachine->getCursorX(), Gmachine->getCursorY())) return buttons[i]->getId();
    return "none";
}

void MMenu::draw() {
    //bg->draw();
    //head->draw();
    for(int i=0; i<buttons.size(); i++)
        buttons[i]->draw();
}

bool MMenu::isDown(std::string b) {
    if(current()==b && Gkeyboard->IsKeyDown(KEY_LBUTTON)){
        //while(Gkeyboard->IsKeyDown(KEY_LBUTTON));
        Gkeyboard->clear(KEY_LBUTTON);
        return true;
    }
    return false;
}
