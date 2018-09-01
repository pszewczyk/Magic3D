#ifndef MPLAYER_H
#define MPLAYER_H

#include "mortal.h"
#include "npc.h"
#include "interface.h"
#include "dcontainer.h"
#include "spellscreen.h"
#include "spellbar.h"

class MPlayer : public MMortal {
protected:
    MBar* hpbar;
    MBar* mpbar;
public:
    MSpellScreen* spellscreen;
    MSpellbar* spellbar;
    MPlayer(CDefsTable*);
    ~MPlayer();
    bool isTalking();
    void setTalking();
    void endTalking();
    string act();
    void useItem(string);
    void updateBars();
    virtual void update();
    bool Control(int);
    bool learnSkill(MAction*);
    void pushToBar(int);

    MWindow* getInventoryScreen();
    MWindow* getSpellScreen();
    MDrawable* genDrawableContainer();
};

#endif
