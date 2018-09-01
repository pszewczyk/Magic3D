#include "game.h"

MGame::MGame(CDefsTable* defs)
{
	config = new CDefsTable(defs->GetString("config","conf.txt"));
    Gkeyboard = new MKeyboard();
    Gmachine = new MMachine(config, Gkeyboard);
    fps = defs->GetInt("fps",60);
    printf("game created\n");
    status="starting";
}

int MGame::loop() {
    //framerate
    framesize = CLOCKS_PER_SEC / fps;
    czas = clock();
    printf("running with %d fps, %d framesize\n", fps, framesize);
    //test menu:
    status="menu";
    mainMenu = new MMenu("Menu g³ówne", Gmachine->getWidth()/2-100, Gmachine->getHeight()/2-100);
    mainMenu->addButton("newgame", "Nowa gra");
    mainMenu->addButton("load", "Wczytaj grê");
    mainMenu->addButton("options", "Opcje");
    mainMenu->addButton("exit", "Zakoñcz");
    printf("menu created, waiting for reaction\n");
    
    while(true){
        if(status=="start") {
            startGame();
        }
        if(status=="end") {
            endGame();
        }
        else if(status=="play") {
            play();
        }
        else if(status=="menu") {
            //powrót do menu = wyczyszczenie syfu
            Gmachine->clearScene();
            //delete mapa;
            menu();
        }
        else if(status=="pause") {
            pause();
        }
        else if(status=="exiting") {
            printf("farewell!\n");
            Gmachine->clearScene();
            Gmachine->dropAll();
            break;
        }
        else if(status=="inventory") {
            printf("opening inventory screen\n");
            inventoryScreen();
        }
        else if(status=="spellscreen") {
            printf("opening spells screen\n");
            spellScreen();
        }
        else if(status=="gameover") {
            printf("YOU ARE DEAD\n");
            gameover();
        }
        else
            printf("unknown status : %s!\n", status.c_str());
    }
    
    return 0;
}

void MGame::play() {
    printf("3d world is ready\n");
    //przywrócenie do poprzedniego stanu ca³ego syfu
    Gmachine->setCursorVisible(false);
    Gmachine->setCursorPos(Gmachine->getWidth()/2,Gmachine->getHeight()/2);
    while(status=="play" && Gmachine->run()) {
        sbar->setValue(mapa->getFps());
        
        //prosty mechanizm stabilizujÃ„â€¦cy szybkoÄ¹â€ºÃ„â€¡ gry na poziomie danego fps
        int over = max(clock() - czas, long(0));   //przy przekroczeniu czasu szybkoÄ¹â€ºÃ„â€¡ zwiÃ„â„¢ksza siÃ„â„¢
        int speed = (5 * (over + framesize)) / framesize;    //ustawienie szybkoÄ¹â€ºci
        czas = clock();
        bool nth = true;
        
        if(Gkeyboard->IsKeyDown(27)) {
            status="pause";
        }
        
        nth = player->Control(speed);
        
        if(Gkeyboard->IsKeyDown('I')) {
            status = "inventory";
            Gkeyboard->clear('I');
            continue;
        }
        if(Gkeyboard->IsKeyDown('K')) {
            status = "spellscreen";
            Gkeyboard->clear('K');
            continue;
        }
        
        MTarget* tar = mapa->getTarget(player);
        player->setTarget(tar);
        
        if(!mob[1]->dead) mob[1]->setAnim("standing_alert");
        if(!mob[2]->dead)mob[2]->setAnim("walking");
        if(!mob[3]->dead)mob[3]->setAnim("prawy_prosty");
        
        mapa->clearFocus();
        if(tar) {
            tar->Focus();
        }
        for(int i=0; i<4; i++) {
            mob[i]->update();
        }
        
        int x = Gmachine->getWidth() / 2;
        int y = Gmachine->getHeight() / 2;
        //sterowanie myszy kamerÃ„â€¦
        cam->translate(Mvector3d(0, Gmachine->getCursorY() - y, 0));
        //player->rotate(Mvector3d(0,Gmachine->getCursorX()-x,0));
        player->TurnRight(Gmachine->getCursorX()-x);
        Mvector3d dir = player->getDirection();
        cam->setRadius(Mvector3d(-dir.x,0,-dir.z));
        
        if(Gkeyboard->IsKeyDown(109)) cam->addDistance(speed);
        if(Gkeyboard->IsKeyDown(107)) cam->addDistance(-speed);
        
        Gmachine->setCursorPos(x, y);
        
        if(!mapa->isLegal(player->x, player->z)) {
            if(!mapa->isLegal(player->x, player->prevz)) player->BackX();
            if(!mapa->isLegal(player->prevx, player->z)) player->BackZ();
        }
        
        //mapa->Minimapa->updatePos(player->cx, player->cy);
       
        //czapka->updateOwner((MMortal*)mob[3]);
        
        if(player->dead) status="gameover";
        player->update();
        
        if(!Gmachine->isWindowActive()) {
            status="pause";
        }
        
        Gmachine->startDrawing(); 

        Gmachine->drawAll(); 
        mapa->draw();
        
        if(player->isTalking()) {
            ((MNpc*)tar)->getTalk()->draw();
        }
        Gmachine->stopDrawing();
        if(clock() < (czas + framesize)) Sleep(czas + framesize-clock());  //czekanie na koniec klatki
    }
}

//pokazuje loadingscreena, ale tylko na jedn¹ klatkê.
//TODO: pasek postêpu
void MGame::showLoadingScreen() {
    MSprite* loading = new MSprite(config->GetString("loadingScreen","pics/loading.bmp"));
    loading->setRect(0,0,Gmachine->getWidth(),Gmachine->getHeight());
    
    Gmachine->startDrawing();
    loading->draw();
    Gmachine->stopDrawing();
    
    delete loading;
}

void MGame::startGame() {
    showLoadingScreen();
    
    mapa = new MMap("maps/samplemap.mmap");
    printf ("starting new game...\n;");
    
    
    CDefsTable* defs = new CDefsTable("config/player.txt");
    player = new MPlayer(defs);
    MDrawable* playerDrawables = player->genDrawableContainer();
    Gmachine->addDrawable(playerDrawables);
    delete defs;
    
    mapa->follow ((MVirMesh*) player);
    cam = mapa->getCamera();
    printf ("camera captured\n");
    cam->linkTarget ((Mvector3d*) player);
    
    defs = new CDefsTable("npcs/tester.txt");
    for(int i=0; i<4; i++) {
        mob[i] = new MNpc(defs);
        mob[i]->x = 1000 + 50*i;
        mob[i]->z = 1000;
        mob[i]->setAnim("standing");
        mob[i]->update_pos();
        mapa->addTarget((MTarget*)mob[i]);
        vector<MItem*> eq = mob[i]->getItems();
        for(int j=0; j<eq.size(); j++) mapa->addTarget((MTarget*)eq[j]);
    }
    
    mob[0]->say("Dzieñ Dobry!");
    delete defs;
    
    
    /*HARDCODED*/
    defs = new CDefsTable("items/czapka1.txt");
    czapka = new MItem(defs);
    czapka->x = 200;
    czapka->z = 200;
    czapka->update_pos();
    //mob[3]->grab(czapka);
    mapa->addTarget((MTarget*)czapka);
    delete defs;
    
    
    defs = new CDefsTable("items/sprys.txt");
    dz = new MItem(defs);
    dz->x = 250;
    dz->z = 250;
    dz->update_pos();
    //mob[3]->grab(dz);
    mapa->addTarget((MTarget*)dz);
    delete defs;
        
    sbar = new MBar();
    sbar->setTexture (Gmachine->getDriver()->getTexture("pics/bar1.bmp"));
    sbar->setMaximum(100);
    sbar->setRect(600,1,100,10);
    sbar->maximize();
    mapa->addSprite ((MSprite*) sbar);
    
    /*podpis = new MLabel();
    podpis->linkPos ((Mvector3d*) player);
    podpis->setRadius (Mvector3d (0, MSCALE, 0));
    podpis->setText ("Leœmur");
    mapa->addSprite ((MSprite*) podpis); */


    MAction* tempaction = new MAction(new CDefsTable("actions/high_kick.txt"));
    player->learnSkill(tempaction);
    player->spellbar->addAction(tempaction,10);
    
    /*koniec HARDCODINGU*/
    status = "play";
    printf("game started\n");
}

void MGame::endGame() {
    showLoadingScreen();
    printf("Ending game...\n");
    
    delete mapa;
    //hardcoded!
    delete player;
    for(int i=0; i<4; i++) delete mob[i];
    Gmachine->clearDrawables();
    
    printf("Gameplay deleted\n");
    
    status="menu";
}

void MGame::menu() {
    Gmachine->addDrawable((MDrawable*)mainMenu);
    mainMenu->setVisible(true);
    Gmachine->setCursorVisible(true);
    while(status=="menu" && Gmachine->run()) {
        if(mainMenu->isDown("newgame")){ status="start"; printf("start!\n"); }
        else if(mainMenu->isDown("exit")){ status="exiting"; printf("exit!\n"); }
        Gkeyboard->clear(KEY_LBUTTON);
        Gmachine->startDrawing();
        Gmachine->drawAll();
        Gmachine->stopDrawing();
        Sleep(30);
    }
    mainMenu->setVisible(false);
}

void MGame::pause() {
    while(Gkeyboard->IsKeyDown(KEY_LBUTTON)); //ochrona przed spamem myszk¹ (dla nerwowych)
    pauseMenu = new MMenu("Pauza", Gmachine->getWidth()/2-100, Gmachine->getHeight()/2-100);
    pauseMenu->addButton("resume", "Graj dalej");
    pauseMenu->addButton("save", "Zapisz grê");
    pauseMenu->addButton("exit", "Wróæ do menu");
    Gmachine->addDrawable((MDrawable*)pauseMenu);
    printf("pause menu created, waiting for reaction\n");
    
    pauseMenu->setVisible(true);
    Gmachine->setCursorVisible(true);
    while(status=="pause" && Gmachine->run()) {
        if(pauseMenu->isDown("resume")) status="play";
        else if(pauseMenu->isDown("exit")) status="end";
        Gmachine->startDrawing();
        Gmachine->drawAll();
        Gmachine->stopDrawing();
        Sleep(30);
    }
    pauseMenu->setVisible(false);
}

void MGame::waiting() {
}

void MGame::inventoryScreen() {
    MWindow* screen = player->getInventoryScreen();
    Gmachine->addDrawable((MDrawable*)screen);
    screen->setVisible(true);
    Gmachine->setCursorVisible(true);
    while(status=="inventory" && Gmachine->run()) {
        if(Gkeyboard->IsKeyDown(KEY_ESCAPE) || Gkeyboard->IsKeyDown('I')) {
            status="play";
            Gkeyboard->clear(KEY_ESCAPE);
            Gkeyboard->clear('I');
        }
        if(Gkeyboard->IsKeyDown(KEY_LBUTTON)) {
            string s = screen->onClick();
            player->useItem(s);
            Gkeyboard->clear(KEY_LBUTTON);
        }
        if(Gkeyboard->IsKeyDown(KEY_RBUTTON)) {
            printf("rbutton is down");
            screen->showCMenu();
            Gkeyboard->clear(KEY_RBUTTON);
        }
        Gmachine->startDrawing();
        Gmachine->drawAll();
        Gmachine->stopDrawing();
        player->checkLife();
        if(player->dead) status="gameover";
        Sleep(30);
    }
    screen->setVisible(false);
    czas = clock();
}

void MGame::gameover() {
    MSprite* napis = new MSprite("pics/gameover.png");
    napis->setRect(0,0,Gmachine->getWidth(),Gmachine->getHeight());
    napis->alfa = 128;    
    
    while(status=="gameover" && Gmachine->run()) {
        if(Gkeyboard->IsKeyDown(KEY_ESCAPE)) {
            status="end";
            Gkeyboard->clear(KEY_ESCAPE);
        }
        Gmachine->startDrawing();
        Gmachine->drawAll();
        napis->draw();
        Gmachine->stopDrawing();
        Sleep(30);
    }
    delete napis;
    czas = clock();
}

void MGame::spellScreen() {
    MWindow* screen = player->getSpellScreen();
    Gmachine->addDrawable((MDrawable*)screen);
    screen->setVisible(true);
    Gmachine->setCursorVisible(true);
    while(status=="spellscreen" && Gmachine->run()) {
        if(Gkeyboard->IsKeyDown(KEY_ESCAPE) || Gkeyboard->IsKeyDown('K')) {
            status="play";
            Gkeyboard->clear(KEY_ESCAPE);
            Gkeyboard->clear('K');
        }
        if(Gkeyboard->IsKeyDown(KEY_LBUTTON)) {
            string s = screen->onClick();
            player->pushToBar(StrToInt(s));
            Gkeyboard->clear(KEY_LBUTTON);
        }
        if(Gkeyboard->IsKeyDown(KEY_RBUTTON)) {
            printf("rbutton is down");
            screen->showCMenu();
            Gkeyboard->clear(KEY_RBUTTON);
        }
        Gmachine->startDrawing();
        Gmachine->drawAll();
        Gmachine->stopDrawing();
        Sleep(30);
    }
    screen->setVisible(false);
    czas = clock();
}
