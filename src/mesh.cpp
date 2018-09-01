#include "mesh.h"

void MVirMesh::scale(Mvector3d s) {
    sizex *= s.x;
    sizey *= s.y;
    sizez *= s.z;
}

Mvector3d MVirMesh::getDirection() {
    double nx = sin(rot.y * 3.14 / 180);
    double nz = cos(rot.y * 3.14 / 180);
    double ny = 0;
    return Mvector3d(2*MSCALE*nx, 2*MSCALE*ny, 2*MSCALE*nz);
}

void MMesh::update_pos()
{
    cx = int(x + (MSCALE / 2)) / MSCALE;
    cy = int(z + (MSCALE / 2)) / MSCALE;
    node->setPosition(vector3df(x,y,z) );
    node->setRotation(vector3df(rot.x, rot.y, rot.z));
    prevx = x;
    prevy = y;
    prevz = z;
}

void MMesh::rotate(Mvector3d a)
{
    rot  = rot + a;
    if(rot.x > 360) rot.x -= 360;
    if(rot.y > 360) rot.y -= 360;
    if(rot.z > 360) rot.z -= 360;
}

void MAnimatedMesh::rotate(Mvector3d a)
{
    rot = rot + a;
    if(rot.x > 360) rot.x -= 360;
    if(rot.y > 360) rot.y -= 360;
    if(rot.z > 360) rot.z -= 360;
}

void MAnimatedMesh::update_pos()
{
    cx = int(x + (MSCALE / 2)) / MSCALE;
    cy = int(z + (MSCALE / 2)) / MSCALE;
    node->setPosition(vector3df(x,y,z) );
    node->setRotation(vector3df(rot.x, rot.y, rot.z));
    prevx = x;
    prevy = y;
    prevz = z;
    //node->setFrameLoop(start, end);
}

Mvector3d MVirMesh::getRot() {
    return rot;
}

void MVirMesh::setRot(Mvector3d a) {
    rot = a;
}

void MVirMesh::denyMove() {
    x = prevx;
    y = prevy;
    z = prevz;
}

void MVirMesh::BackX() {
    x = prevx;
}

void MVirMesh::BackY() {
    y = prevy;
}

void MVirMesh::BackZ() {
    z = prevz;
}

void MAnimatedMesh::setVisible(bool b) {
    node->setVisible(b);
}

void MMesh::drop()
{
     node->drop();
}

void MAnimatedMesh::drop()
{
     node->drop();
}

MVirMesh::MVirMesh()
	: Mvector3d()
	, sizex(0)
	, sizey(0)
	, sizez(0)
	, rot(Mvector3d(0,0,0))
	, prevx(0)
	, prevy(0)
	, prevz(0)
	, cx(0)
	, cy(0)
{
}

MAnimatedMesh::MAnimatedMesh()
	: MVirMesh()
	, mesh(0)
	, node(0)
	, texture(0)
	, start(0)
	, end(0)
	, anims()
{
 sizex = MSCALE;
 sizey = MSCALE;
 sizez = MSCALE;
 /* Konstruktory Mvector3d (dla xyz) i MVirMesh(dla rot) juz zapodaja takie wartosci, nie ma sensu znowu dawac takich samych
 x=0;
 y=0;
 z=0;
 rot = Mvector3d(0,0,0);
 */
 addAnim("default", 0, 0);
}

MMesh::MMesh()
	: MVirMesh()
	, mesh(0)
	, node(0)
	, texture(0)
{
 sizex = MSCALE;
 sizey = MSCALE;
 sizez = MSCALE;
 /*
 x=0;
 y=0;
 z=0;
 rot = Mvector3d(0,0,0);
 */
}

void MAnimatedMesh::loadModel(string filename) {
    printf("loading model from %s\n", filename.c_str());
        
    CDefsTable* defs = new CDefsTable(filename);
    setMesh(Gmachine->getMesh(defs->GetString("model")));
    setTexture(Gmachine->getTexture(defs->GetString("texture")));
    
    node = Gmachine->getManager()->addAnimatedMeshSceneNode(mesh);
    node->setScale (core::vector3df(sizex, sizey, sizez));
    node->setPosition (core::vector3df(x, y, z));
    //Obczaiæ wiêcej mo¿liwoœci materia³ów
    node->setMaterialFlag (video::EMF_LIGHTING, false);
    
    CDefsTable* animsDefs = defs->GetTable("anims");
    vector<string> names = animsDefs->GetWartosci();
    for(int i=0; i<names.size(); i++) {
        vector<int> v;
        v = animsDefs->GetIntList(names[i]);
        addAnim(names[i], v[0], v[1]);
    }
    
    setAnim("default");
    
    node->setFrameLoop (start, end);
    update_texture();
    
    delete defs;
}

void MMesh::localTrans(Mvector3d a) {
    x += (cos(rot.y) * a.x) + (sin(rot.y) * a.z);
    z += (cos(rot.y) * a.z) - (sin(rot.y) * a.x);
    y += a.y;
}

void MAnimatedMesh::localTrans(Mvector3d a) {
    x += (cos(rot.y * 3.14 / 180) * a.x) + (sin(rot.y * 3.14 / 180) * a.z); //(cos(rot.y) * a.x) + (sin(rot.y) * a.z);
    y += a.y;
    z += (cos(rot.y * 3.14 / 180) * a.z) - (sin(rot.y * 3.14 / 180) * a.x);
}

bool MAnimatedMesh::setAnim(int s, int e)
{
    if((start == s) && (end == e)) return false;
    start = s;
    end = e;
    node->setFrameLoop(start, end);    //bug!
    /* Okazuje siê, ¿e obiekt musi byæ juz podlinkowany w managerze, zanim bêdzie
    mo¿na mu ustawiæ frameloop.
    */
    return true;
}

bool MAnimatedMesh::setAnim(string label) {
    if(anims.find(label) != anims.end()) {
        int s = anims[label].first;
        int e = anims[label].second;
        setAnim(s,e);
        return true;
    }
    return false;
}

bool MAnimatedMesh::addAnim(string label, int s, int e) {
    if(s <= e) {
        anims[label] = make_pair(s,e);
        return true;
    }
    return false;
}

void MAnimatedMesh::setMesh(IAnimatedMesh* a)
{
     mesh = a;
}

void MMesh::setMesh(IMesh* a)
{
     mesh = a;
}

void MMesh::setTexture(ITexture* tex)
{
     texture = tex;
}

void MAnimatedMesh::setTexture(ITexture* tex)
{
     texture = tex;
}

void MAnimatedMesh::linkManager(ISceneManager* manager)
{
    node = manager->addAnimatedMeshSceneNode(mesh);
    node->setScale (core::vector3df(sizex, sizey, sizez));
    node->setPosition (core::vector3df(x, y, z));
    node->setMaterialFlag (video::EMF_LIGHTING, false);
    node->setFrameLoop (start, end);
    update_texture();
}

void MMesh::linkManager(ISceneManager* manager)
{
    node = manager->addMeshSceneNode(mesh);
    node->setScale (core::vector3df(sizex, sizey, sizez));
    node->setPosition (core::vector3df(x, y, z));
    node->setMaterialFlag (video::EMF_LIGHTING, false);
    update_texture();
}

void MMesh::update_texture()
{
     node->setMaterialTexture(0, texture);
}

void MAnimatedMesh::update_texture()
{
     node->setMaterialTexture(0, texture);
}

MField::MField()
	: MMesh()
	, xc(0)
	, yc(0)
{
}

//pa³owane, dorobiæ normalne efekty
void MAnimatedMesh::setFocus(bool b) {
    if(b) node->setMaterialType(video::EMT_LIGHTMAP);
    else node->setMaterialType(video::EMT_SOLID);
}

int MAnimatedMesh::getFrame() {
    return (int)node->getFrameNr();
}

int MAnimatedMesh::getStartFrame() {
    return start;
}

int MAnimatedMesh::getEndFrame() {
    return end;
}
