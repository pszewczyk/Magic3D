#include "interface.h"

MBar::MBar()
	: value(1)
	, maximum(1)
{
    X = Y = 1;
    Height = 10;
}

MBar::MBar(int max, string tex)
	: value(max)
	, maximum(max)
{
    setTexture(Gmachine->getDriver()->getTexture(tex.c_str()));
    X = Y = 1;
    Height = 10;
}

void MBar::setTexture(ITexture* t) {
    texture = t;
}
void MBar::setValue(int v) {
    value = v;
}
void MBar::setWidth(int w) {
    Width = w;
}
void MBar::setMaximum(int m) {
    maximum = m;
}
void MBar::maximize() {
    value = maximum;
}
int MBar::getMaximum() {
    return maximum;
}
int MBar::getValue() {
    return value;
}

MSprite::MSprite()
	: texture(0)
	, font(Gmachine->getGuienv()->getFont("fonts/nyala.xml"))
	, alfa(255)
{
    Gmachine->getDriver()->makeColorKeyTexture (texture, SColor(0, 255, 0, 255));
    font = Gmachine->getDevice()->getGUIEnvironment()->getFont("fonts/nyala.xml");
}

MSprite::MSprite(string filename)
	: texture(Gmachine->getDriver()->getTexture(filename.c_str()))
	, font(Gmachine->getGuienv()->getFont("fonts/nyala.xml"))
	, alfa(255)
{
    Gmachine->getDriver()->makeColorKeyTexture (texture, SColor(0, 255, 0, 255));
    font = Gmachine->getDevice()->getGUIEnvironment()->getFont("fonts/nyala.xml");
}

MSprite::~MSprite() {
    printf("another sprite deleted\n");
}

void MSprite::draw() {
    Gmachine->getDriver()->draw2DImage(texture, position2d <s32> (X,Y), rect <s32> (0, 0, Width, Height), 0, SColor(alfa, 255, 255, 255), true);
    //font->draw("sample", core::rect <s32> (130, 1, 300, 50), video::SColor(255, 255, 255, 255));
}

void MBar::draw() {
    int w = (Width * value) / maximum;
    Gmachine->getDriver()->draw2DImage(texture, position2d <s32> (X,Y), rect <s32> (0, 0, w, Height), 0, SColor(128, 255, 255, 255), true);
    char buff[32];
    sprintf(buff, "%d", value);
    font->draw(buff, core::rect <s32> (X+w+5, Y, 300, 20), video::SColor(255, 255, 255, 255));
}

MBar::~MBar() {
    
}

MText::MText(int a, int b, string t)
    : text(t)
    , font(Gmachine->getDefaultFont()) 
    , color(video::SColor(255,255,255,255))
{
    X = a;
    Y = b;
}

MText::MText(string t)
    : text(t)
    , font(Gmachine->getDefaultFont()) 
    , color(video::SColor(255,255,255,255))
{
    Width = 300;
    Height = 50;
}

void MText::draw() {
    
    font->draw(StrToWstr(text).c_str(), core::rect <s32> (X, Y, Width, Height), color);
}

void MText::setColor(int a, int r, int g, int b) {
    color = video::SColor(a,r,g,b);
}

MButton::MButton(string i, string t)
    : MSprite()
    , text(t)
    , id(i)
{
}

void MButton::draw() {
    wstring w = StrToWstr(text);
    video::SColor color(255, 255, 255, 255);
    if(hover()) color = video::SColor(255,255,200,100);
    font->draw(w.c_str(), core::rect <s32> (X, Y, Width, Height), color);
}

bool MButton::hover(int xPos, int yPos) {
    return xPos>=X && yPos>=Y && xPos<=X+Width && yPos<=Y+Height;
}

//bez pa³owania rzymu nie zbudowano
bool MButton::hover() {
    int xPos = Gmachine->getCursorX();
    int yPos = Gmachine->getCursorY();
    return xPos>=X && yPos>=Y && xPos<=X+Width && yPos<=Y+Height;
}

string MButton::getId() {
    return id;
}

MSpeak::MSpeak(string s, Mvector3d* m)
    : speaker(m)
    , text(s)
{
    texture = Gmachine->getTexture("pics/dymek1.png");
}

MSpeak::~MSpeak() {
}

void MSpeak::draw() {
    position2d <s32> p = Gmachine->getManager()->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(vector3df (speaker->x, speaker->y+MSCALE, speaker->z));
    Gmachine->getDriver()->draw2DImage(texture, position2d <s32> (p.X-10,p.Y-100), rect <s32> (0, 0, 350, 100), 0, SColor(128, 255, 255, 255), true);
    wstring w = StrToWstr(BreakLines(text,55));
    font->draw(w.c_str(), core::rect <s32> (p.X , p.Y-90, 100, 70), video::SColor(255, 0, 0, 0));
}

void MSpeak::setText(string s) {
    text = s;
}
