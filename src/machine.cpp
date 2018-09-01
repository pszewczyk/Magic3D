#include "machine.h"

MMachine::MMachine(CDefsTable* defs, MKeyboard* keyboard)
    : windowWidth(defs->GetInt("resX", 800))
    , windowHeight(defs->GetInt("resY", 600))
    , fullscreen(defs->GetBool("fullscreen", false))
    , fps(defs->GetInt("fps", 60))
    , device(createDevice(EDT_OPENGL, dimension2d <u32> (windowWidth, windowHeight), 32, fullscreen, false, false, keyboard))
    , driver(device->getVideoDriver())
	, manager(device->getSceneManager())
	, guienv(device->getGUIEnvironment())
	, cursor(device->getCursorControl())
{
    //printf("now writing in logfile\n");
    //LogStdout(defs->GetString("logfile", "defaultlog.log"));
    printf("device created, res %d x %d\n", windowWidth, windowHeight);
    srand(time(NULL));
}

//wywalenie pustych wskaŸników na syf
void MMachine::checkEr() {
    for(vector<MDrawable*>::iterator it=drawables.begin(); it!=drawables.end(); it++)
        if(*it==NULL || !(*it)) {
            it=drawables.erase(it);
            printf("another drawable erased from list\n");
        }
}

/*MItem* MMachine::getItem(string filename) {
    CDefsTable* defs = new CDefsTable(filename);
    MItem* result = new MItem(defs);
    result->setVisible(false);
    targets.push_back(result);
    delete defs;
    return result;
}*/

void MMachine::addDrawable(MDrawable* d) {
    drawables.push_back(d);
}

void MMachine::clearDrawables() {
    drawables.clear();
}

IrrlichtDevice* MMachine::getDevice() {
    return device;
}
IVideoDriver* MMachine::getDriver(){
    return driver;
}
ISceneManager* MMachine::getManager(){
    return manager;
}
IGUIEnvironment* MMachine::getGuienv(){
    return guienv;
}
int MMachine::getWidth() {
    return windowWidth;
}
int MMachine::getHeight() {
    return windowHeight;
}

void MMachine::startDrawing() {
    driver->beginScene(true, true, SColor(255, 100, 100, 120));
}

void MMachine::stopDrawing() {
    driver->endScene();
}

void MMachine::drawAll() {
    manager->drawAll();
    for(int i=0; i<drawables.size(); i++) {
        if(drawables[i] && drawables[i]->getVisible()) {
            drawables[i]->draw();
        }
    }
}

void MMachine::dropAll() {
    device->drop();
}

bool MMachine::isWindowActive() {
    return device->isWindowActive();
}

void MMachine::setCursorVisible(bool a) {
    cursor->setVisible(a);
}
void MMachine::setCursorPos(int x, int y) {
    cursor->setPosition(x,y);
}
int MMachine::getCursorX() {
    return cursor->getPosition().X;
}
int MMachine::getCursorY() {
    return cursor->getPosition().Y;
}

bool MMachine::run() {
    return device->run();
}

void MMachine::clearScene() {
    manager->clear();
}

IAnimatedMesh* MMachine::getMesh(string filename) {
    return manager->getMesh(filename.c_str());
}
ITexture* MMachine::getTexture(string filename) {
    return driver->getTexture(filename.c_str());
}

IGUIFont* MMachine::getDefaultFont() {
    return device->getGUIEnvironment()->getFont("fonts/nyala.xml");
}

void MMachine::LogStdout(string filename) {
    /*FILE* fap=*/ freopen(filename.c_str(), "w+", stdout);
}

int MMachine::random(int n) {
    return rand()%n;
}
