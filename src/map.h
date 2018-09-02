#ifndef MMAP_H
#define MMAP_H

#include "drawable.h"
#include "world.h"
#include "mortal.h"
#include "minimap.h"

//Klasa mapy
class MMap : public MWorld {
private:
    int xSize;
	int ySize;    //dziwny rozmiar mapy
    vector<vector<bool> > clear;    //zawiera info czy pole jest przejezdne
    vector<vector<Meshlist> > fields; //to nie wiem jeszcze po co jest    
    vector<vector<MMesh*> > terrain;    //planey terenu
    
    vector<MTarget*> targets;   //targety do namierzenia
    
public:
    MMinimap* Minimapa;
    MMap();
    ~MMap();
    MMap(int, int);
    MMap(std::string);
    bool loadFile(std::string); //wczytaj mapê z pliku
    void genTerrain();  //wygeneruj obiekt terenu (mesha)
    bool isLegal(float, float);
    void setMem();

    void addTarget(MTarget*);    
    MTarget* getTarget(MMortal*);
    void clearFocus();
    //~MMap();
};


#endif
