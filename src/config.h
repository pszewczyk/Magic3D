#ifndef IRCONF_H
#define IRCONF_H

#define MSCALE 100
#define PIERDYLIARD 100000000
#define GFXPREFIX "gfx/"
#define MALLOWED_DISTANCE 1000

#include <map>
#include <string>
#include <queue>
#include <stack>
#include <vector>

#ifdef WIN_32
#include <windows.h>
#define clock_ms() clock()
#else
#include <unistd.h>
#define Sleep(ms) usleep(ms * 1000)
#define clock_ms() ((clock()*1000)/CLOCKS_PER_SEC)
#endif

//kolejne rage na usingi. Chyba jednak dev nie radzi sobie z niktórymi projektami.
#if 0
#define string std::string
#define wstring std::wstring
#define vector std::vector
#define map std::map
#define ifstream std::ifstream
#define ofstream std::ofstream
#define cout std::cout
#define pair std::pair
#define make_pair std::make_pair
#define queue std::queue
#endif

//pamiêtaæ, ¿e w irrlichcie mo¿e pojawiæ siê zmienna nazwana vector, wiêc config.h do³¹czaæ na koñcu.
/*
using std::string;
using std::wstring;
using std::vector;
using std::map;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::pair;
using std::make_pair;
*/

#endif
