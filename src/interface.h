#ifndef MINTERFACE_H
#define MINTERFACE_H

#include <irrlicht.h>

#include <vector>
#include <string>

#include "globalcrap.h"
#include "primitives.h"
#include "drawable.h"
#include "io.h"
//#include "config.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

//podstawowy element interfejsu 2d
class MSprite : public MDrawable{
protected:
    ITexture* texture;
    IGUIFont* font;
public:
    int alfa;
    MSprite();
    MSprite(string filename);
    ~MSprite();
    virtual void draw();
};

class MBar : public MSprite{
private:
    int value;
    int maximum;
public:
    MBar();
    ~MBar();
    MBar(int max, string tex);
    void setTexture(ITexture*);
    void setValue(int);
    void setMaximum(int);
    void maximize();
    void setWidth(int);
    int getMaximum();
    int getValue();
    void draw();
};

class MText : public MDrawable{
private:
    string text;
    IGUIFont* font;
    video::SColor color;
    MText();
public:
    MText(int, int, string);
    MText(string);
    void setColor(int, int, int, int);
    virtual void draw();
};

class MButton : public MSprite {
private:
    string text;
    string id;
public:
    MButton(string id, string text);
    bool hover(int xPos, int yPos);
    bool hover();
    string getId();
    void focus();
    void unfocus();
    void draw();
};

class MSpeak : public MSprite {
private:
    string text;
    Mvector3d* speaker;
public:
    MSpeak(string, Mvector3d*);
    ~MSpeak();
    
    void setText(string);    
    void draw();
};

#endif
