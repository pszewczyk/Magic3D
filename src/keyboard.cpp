#include "keyboard.h"

MKeyboard::MKeyboard()
{
 for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i) KeyIsDown[i] = false;
}

bool MKeyboard::IsKeyDown( int keyCode )
{
//return GetAsyncKeyState(keyCode);
    return KeyIsDown[keyCode];
}

void MKeyboard::clear( int keyCode )
{
    KeyIsDown[keyCode] = false;
}


bool MKeyboard::OnEvent(const SEvent& event) {
// Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == EET_MOUSE_INPUT_EVENT) {
        KeyIsDown[KEY_LBUTTON] = event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN;
        KeyIsDown[KEY_RBUTTON] = event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN;
    }
    return false;
}
