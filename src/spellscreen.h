#ifndef MSPELLSCREEN_H
#define MSPELLSCREEN_H

#include "window.h"
#include "action.h"

class MSpellScreen : public MWindow {
private:
    MAction* ContextAction;
    string keynames[12];
public:
    vector<MAction*> slots;
    MSpellScreen();
    //MSpellScreen(CDefsTable*);
    ~MSpellScreen();
    bool learn(MAction*);
    //bool pick(MAction*, int=10);
    //bool unpick(MAction*);
    bool forget(MAction*);
    virtual void draw();
    string onClick();
    void showCMenu();
    MAction* getContextAction();
};

#endif
