#ifndef MSPELLBAR_H
#define MSPELLBAR_H

#include "action.h"
#include "dcontainer.h"
#include "interface.h"

class MSpellbar : public MDrawableContainer {
private:
    MSprite* bg;
    MAction* actions[12];
    int Keys[12];
    int CurrentSpell;
public:
    MSpellbar();
    ~MSpellbar();
    void draw();
    void addAction(MAction*, int);
    MAction* getAction();
    void SpellEnd();
};

#endif
