#include "world.h"

MWorld::MWorld()
    : objects()
	, images(0)
	, camera(new MCamera( Mvector3d (MSCALE * 1.0, MSCALE * 1.5, -MSCALE * 2.0))) //pamietac o delete!
	, timer(0)
	, curr_fps(0)
	, fps(0)
	, sprites()
{
    printf("world created\n");
    Gmachine->getDevice()->setWindowCaption(L"Magic3d");
    camera->linkManager(Gmachine->getManager());
    //manager->addCameraSceneNode(0, vector3df(SCALE, SCALE * 1.5, -SCALE * 2), vector3df(0,0,0))
}

MWorld::~MWorld() {
    sprites.clear();
    
}

MCamera* MWorld::getCamera() {
    return camera;
}

bool MWorld::run() {
    return Gmachine->getDevice()->run();
}

void MWorld::draw() {
    camera->update();
	++curr_fps;
    int c = clock();
    if(c-timer > CLOCKS_PER_SEC)
    {
        timer += CLOCKS_PER_SEC;
        fps = curr_fps;
        curr_fps = 0;
    }
    for(int i=0; i<sprites.size(); i++) {
        sprites[i]->draw();
    }
}

int MWorld::getFps() {
    return fps;
}

void MWorld::addSprite(MSprite* s) {
    sprites.push_back(s);
}

/*MAnimatedMesh* MWorld::load_irg(string filename)
{
    //pamiêtaæ o zachowaniu kolejnoœci
     MAnimatedMesh* m = new MAnimatedMesh();
     objects.push_back((MVirMesh*) m);
     ifstream in;
     in.open(filename.c_str());
     string model, tex;
     in >> model >> tex;
     m->setMesh(Gmachine->getManager()->getMesh(model.c_str()));
     m->setTexture(Gmachine->getDriver()->getTexture(tex.c_str()));
     m->linkManager(Gmachine->getManager());
     int c, s, e;
     string label;
     in >> c;
     for(int i = 0; i < c; ++i) {
        in >> label >> s >> e;
        m->addAnim(label, s, e);
    }
    m->setAnim("default");

    return m;
}*/

void MWorld::follow(MVirMesh *l) {
}
