//By severus

#include "game.h"
int main()
{
    CDefsTable* defs = new CDefsTable("game.txt");
    MGame* game = new MGame(defs);
    game -> loop();
    delete game;
	return 0;
}
