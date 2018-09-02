#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include "mesh.h"
#include "primitives.h"
#include "config.h"
#include "camera.h"
#include "interface.h"
#include "defstable.h"
#include "machine.h"
#include "globalcrap.h"

typedef vector<MVirMesh*> Meshlist;

//Abstrakcyjna klasa œwiata
class MWorld : MDrawable{
protected:   
    Meshlist objects;	
    ITexture* images;
    MCamera* camera;
    
    int timer;
	int curr_fps;
	int fps;
    vector<MSprite*> sprites;
public:
    MWorld();   //konstruktor
    ~MWorld();
    int getFps();
    void addSprite(MSprite*);
    void draw();
    bool run();     //odpal device irrlichta
    void set_camera(vector3df, vector3df); //ustaw kamerê (wektor pozycji i orientacji)
    MCamera* getCamera();
    //MAnimatedMesh* load_irg(std::string);    //wczytaj mesha z pliku (zwraca wskaŸnik na za³adowane)
    //czemu ma to robiæ œwiat?
    void follow(MVirMesh*);   //przywiaz kamere do obiektu
};
#endif
