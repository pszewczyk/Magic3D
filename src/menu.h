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
    string title;
    int x, y, width, buttonHeight;
public:
    MMenu(string, int, int);
    MMenu(string, int, int, int, int);
    ~MMenu();
    void draw();
    void addButton(MButton*);
    void addButton(string id, string text);
    string current();
    bool isDown(string);
};

#endif
