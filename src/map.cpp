#include "map.h"

void MMap::genTerrain() {
    printf("genering terrain...\n");
    for(int i = 0; i < xSize; i++)
	for(int j = 0; j < ySize; j++) {
		MField* m = new MField();
		m->setMesh(Gmachine->getManager()->getMesh("models/basic_plane.3ds"));
		m->setTexture(Gmachine->getDriver()->getTexture("models/basic_plane.bmp"));
		m->translate(Mvector3d(MSCALE * i, 0, MSCALE * j));
		m->linkManager(Gmachine->getManager());
	}
    printf("Terrain generated\n");
    
}

void MMap::setMem() {
    clear.resize(xSize);
    for(int i = 0; i < xSize; i++) clear[i].resize(ySize);
    fields.resize(xSize);
    for(int i = 0; i < xSize; i++) fields[i].resize(ySize);
    terrain.resize(xSize);
    for(int i = 0; i < xSize; i++) terrain[i].resize(ySize);
}

    int xSize;
	int ySize;    //dziwny rozmiar mapy
    vector<vector<bool> > clear;    //zawiera info czy pole jest przejezdne
    vector<vector<Meshlist> > fields; //to nie wiem jeszcze po co jest    
    vector<vector<MMesh*> > terrain;    //planey terenu

MMap::MMap()
	: MWorld()
	, xSize(4)
	, ySize(4)
	, clear()
	, fields()
	, terrain()
{
    printf("Creating map...\n");
    setMem();      
    genTerrain();
    printf("Map created\n");
}

MMap::~MMap() {
    clear.clear();
    fields.clear();
    terrain.clear();
}

MMap::MMap(int x, int y)
	: MWorld()
	, xSize(x)
	, ySize(y)
	, clear()
	, fields()
	, terrain()
{
    printf("Creating map...\n");
    setMem();
    genTerrain();
    printf("Map created\n");
}

MMap::MMap(std::string filename)
	: MWorld()
	, xSize(0)
	, ySize(0)
	, clear()
	, fields()
	, terrain()
{
    printf("Loading map from file %s...\n", filename.c_str());
    ifstream in;
    in.open(filename.c_str());
    in >> xSize;
    in >> ySize;

    setMem();
    char buff[xSize][ySize];
    for(int i = 0; i < xSize; i++)
	for(int j = 0; j < ySize; j++) {
		do {
			buff[i][j] = in.get();
		} while(buff[i][j] == '\n');

		if(buff[i][j] == '.') clear[i][j] = true;
		else clear[i][j] = false;
	}
    int n;
    in >> n;
    for(int k = 0; k < n; k++) {
        char c;
        std::string name;
        in >> c;
        in >> name;
        
        for(int i = 0; i < xSize; i++)
		for(int j = 0; j < ySize; j++)
			if(buff[i][j] == c) {
				MAnimatedMesh* m = new MAnimatedMesh();
				m->loadModel(name);
				objects.push_back((MVirMesh*) m);
				m->x = MSCALE * i;
				m->y = 0;
				m->z = MSCALE * j;
				m->update_pos();
				//printf("%d %d\n", m->x, m->z);
			}
    }
    genTerrain();
    //Minimapa = new MMinimap(clear);
    //Gmachine->addDrawable(Minimapa);
    //Minimapa->setVisible(true);
    printf("Map loaded!\n");
}

bool MMap::isLegal(float x, float y) {
    //if(x<-MSCALE/2 && y<-MSCALE/2) return false;
    x += MSCALE / 2;
    y += MSCALE / 2;
    if((x < 0) || (y < 0)) return false;
    int nx = (int)x / MSCALE;
    int ny = (int)y / MSCALE;
    return (nx < xSize) && (ny < ySize) && (nx >= 0) && (ny >= 0) && clear[nx][ny];
}


void MMap::addTarget(MTarget* t) {
    targets.push_back(t);
}

MTarget* MMap::getTarget(MMortal* m) {
    MTarget* result = NULL;
    double los = 200;
    double aos = 0.75;
    double dist = los;
    for(int i=0; i<targets.size(); i++) {
        Mvector3d d = (*(Mvector3d*)targets[i]-*(Mvector3d*)m);
        if(d.length()<dist && cosangle3d(d, m->getDirection())>aos && targets[i]->selectable) {
            result = targets[i];
            dist = d.length();
        }
    }
    return result;
}

void MMap::clearFocus() {
    for(int i=0; i<targets.size(); i++) {
        targets[i]->unFocus();
    }
}
