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
    MSprite(std::string filename);
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
    MBar(int max, std::string tex);
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
    std::string text;
    IGUIFont* font;
    video::SColor color;
    MText();
public:
    MText(int, int, std::string);
    MText(std::string);
    void setColor(int, int, int, int);
    virtual void draw();
};

class MButton : public MSprite {
private:
    std::string text;
    std::string id;
public:
    MButton(std::string id, std::string text);
    bool hover(int xPos, int yPos);
    bool hover();
    std::string getId();
    void focus();
    void unfocus();
    void draw();
};

class MSpeak : public MSprite {
private:
    std::string text;
    Mvector3d* speaker;
public:
    MSpeak(std::string, Mvector3d*);
    ~MSpeak();
    
    void setText(std::string);    
    void draw();
};

#endif
