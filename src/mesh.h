#ifndef MESH_H
#define MESH_H

#include <irrlicht.h>
#include <vector>
#include <string>
#include <fstream>
#include <map>
//#include <windows.h>
#include <cmath>

#include "primitives.h"
#include "drawable.h"
#include "defstable.h"
#include "globalcrap.h"
#include "config.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//abstrakt ³¹cz¹cy animowany i nieanimowany mesh, w gruncie rzeczy podobne
class MVirMesh : public Mvector3d
{
protected:       
    //Parametry
    //TODO: zmienic size z int,int,int na Mvector3d
       float sizex;
       float sizey;
       float sizez;
       Mvector3d rot;
       
public:
        double prevx;
	    double prevy;
	    double prevz;
        int cx;
        int cy;
        MVirMesh();
        Mvector3d getDirection();
        Mvector3d getRot();
        void setRot(Mvector3d);
        virtual void update_texture() = 0;
        virtual void drop() = 0;
        //virtual void setMesh(IAnimatedMesh*) = 0;
        virtual void setTexture(ITexture*) = 0;
        virtual void update_pos() = 0;
        virtual void rotate(Mvector3d) = 0;
        virtual void linkManager(ISceneManager*) = 0;  //Dodanie syfu do managera z wy¿szych poziomów
        virtual void localTrans(Mvector3d) = 0;
        void scale(Mvector3d);
        void denyMove();
        void BackX();
        void BackY();
        void BackZ();
};

class MMesh : public MVirMesh {
protected:
    //Irrlicht objects
       IMesh* mesh;
       IMeshSceneNode* node;
       ITexture* texture;
public:
       MMesh();
       void update_texture();
       void drop();
       void setMesh(IMesh*);
       void setTexture(ITexture*);
       void update_pos();
       void rotate(Mvector3d);
       void localTrans(Mvector3d);
       void linkManager(ISceneManager*);  //Dodanie syfu do managera z wy¿szych poziomów
};

class MAnimatedMesh : public MVirMesh {
protected:
    //Irrlicht objects
       IAnimatedMesh* mesh;
       IAnimatedMeshSceneNode* node;
       ITexture* texture;
       int start;
       int end;
       std::map<std::string, std::pair<int, int> > anims;
public:
       MAnimatedMesh();
       void loadModel(std::string filename);
       void update_texture();
       void drop();
       void setMesh(IAnimatedMesh*);
       void setTexture(ITexture*);
       void update_pos();
       void rotate(Mvector3d);
       void localTrans(Mvector3d);
       void linkManager(ISceneManager*);  //Dodanie syfu do managera z wy¿szych poziomów
       bool setAnim(int, int);
       bool setAnim(std::string);
       bool addAnim(std::string, int, int);
       void setFocus(bool);
       int getFrame();
       int getStartFrame();
       int getEndFrame();
       void setVisible(bool);
};

class MField : public MMesh{
private:
    int xc;
	int yc; //wspó³rzêdne na mapie
public:
    MField();
};


#endif
