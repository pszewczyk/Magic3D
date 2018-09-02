#ifndef MACTION_H
#define MACTION_H

#include <string>

#include "icon.h"
#include "defstable.h"
#include "config.h"

class MAction {
public:
    std::string id;
    MIcon* icon;
    std::string anim;
    int castingTime;
    int duration;       //czas trwania, 0 oznacza natychmiastowy efekt (sta³y)
    int dist;       //min odleglosc, 0 oznacza brak zakresu
    bool multitarget;
    std::string name;
    public:
    std::map<std::string, int> effects;
    std::map<std::string, int> selfEffects;
    MAction(CDefsTable* defs);
    void cast();
};

#endif
