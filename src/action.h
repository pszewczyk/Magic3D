#ifndef MACTION_H
#define MACTION_H

#include <string>

#include "icon.h"
#include "defstable.h"
#include "config.h"

class MAction {
public:
    string id;
    MIcon* icon;
    string anim;
    int castingTime;
    int duration;       //czas trwania, 0 oznacza natychmiastowy efekt (sta³y)
    int dist;       //min odleglosc, 0 oznacza brak zakresu
    bool multitarget;
    string name;
    public:
    map<string, int> effects;
    map<string, int> selfEffects;
    MAction(CDefsTable* defs);
    void cast();
};

#endif
