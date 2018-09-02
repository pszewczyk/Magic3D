#ifndef MMENU_H
#define MMENU_H

#include <vector>
#include <string>

#include "drawable.h"
#include "interface.h"
#include "config.h"

class MMenu : public MDrawable{
private:
    MSprite* bg;
    MSprite* head;
    vector<MButton*> buttons;
    std::string title;
    int x, y, width, buttonHeight;
public:
    MMenu(std::string, int, int);
    MMenu(std::string, int, int, int, int);
    ~MMenu();
    void draw();
    void addButton(MButton*);
    void addButton(std::string id, std::string text);
    std::string current();
    bool isDown(std::string);
};

#endif
