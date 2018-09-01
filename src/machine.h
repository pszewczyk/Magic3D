#ifndef MMACHINE_H
#define MMACHINE_H

#include <irrlicht.h>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#ifdef WIN_32
#include <windows.h>
#endif
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//#include "item.h"
#include "drawable.h"
#include "keyboard.h"
#include "defstable.h"
#include "config.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class MMachine {
private:
    int windowWidth;
	int windowHeight;
	int fps;
	bool fullscreen;
	
	//lista drawabli
	vector<MDrawable*> drawables;
public:	
    //Irrlichtowe obiekty
    IrrlichtDevice* device;
    IVideoDriver* driver;
    ISceneManager* manager;
    IGUIEnvironment* guienv;
    ICursorControl* cursor;
    
    //vector<MTarget*> targets;
    void checkEr();
    MMachine(CDefsTable* defs, MKeyboard* keyboard);
    IrrlichtDevice* getDevice();
    IVideoDriver* getDriver();
    ISceneManager* getManager();
    IGUIEnvironment* getGuienv();
    ICursorControl* getCursor();
    
    //MItem* getItem(string filename);
    
    void setCursorVisible(bool);
    void setCursorPos(int x, int y);
    int getCursorX();
    int getCursorY();
    
    int getWidth();
    int getHeight();
    void addDrawable(MDrawable* d);
    void clearDrawables();
    void startDrawing();
    void stopDrawing();
    void drawAll();
    void dropAll(); //wyczyœæ obiekty Irrlichta
    bool run();
    bool isWindowActive();
    void clearScene();
    
    IGUIFont* getDefaultFont();
    
    IAnimatedMesh* getMesh(string filename);
    ITexture* getTexture(string filename);
    
    void LogStdout(string);
    
    int random(int);
};

#endif
