/*
keyboard.h - obs³uga klawiatury
*/

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <irrlicht.h>
//#include <windows.h>
#include <vector>
#include <time.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class MKeyboard : public IEventReceiver
{
private:
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
public:
       MKeyboard();
        bool IsKeyDown(int);
        /* Kody klawiszy ascii odpowiadaj¹ swoim kodom, do reszty patrz strona microsoftu */
        void clear(int);
        virtual bool OnEvent(const SEvent& event);
};

#endif

