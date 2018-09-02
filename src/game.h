/*
game.h - G³ówny plik projektu, podstawowa klasa gry
*/
#ifndef GAME_H
#define GAME_H

#include <vector>
#ifdef WIN_32
#include <windows.h>
#endif
#include <math.h>
#include <time.h>

#include "map.h"
#include "mesh.h"
#include "keyboard.h"
#include "player.h"
#include "npc.h"
#include "item.h"
#include "menu.h"
#include "window.h"
#include "config.h"
#include "defstable.h"
#include "globalcrap.h"

class MGame
{
private:
        CDefsTable* config;
        MMap* mapa;
        MMenu* mainMenu;
        MMenu* pauseMenu;
        int fps;
	std::string status;
        int framesize;
        int czas;
        
        //zmienne gry (póŸniej zrobiæ porz¹dek)
        MPlayer* player;
        MNpc* mob[4];
        MItem* czapka;
        MItem* dz;
        MCamera* cam;
        MBar* sbar;
        //MDrawableContainer* podpis;
public:
       MGame(CDefsTable* defs);
       int loop();  //g³ówna pêtla
       
       void startGame();
       void endGame();
       void play();
       void menu();
       void waiting();
       void pause();
       void showLoadingScreen();
       void inventoryScreen();
       void spellScreen();
       void gameover();
};

#endif
