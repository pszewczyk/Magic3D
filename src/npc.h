#ifndef MNPC_H
#define MNPC_H

#include <string>

#include "interface.h"
#include "mortal.h"
#include "question.h"
#include "defstable.h"
#include "config.h"

class MNpc : public MMortal {
private:
    MTalk* talk;
    MBar* hpbar;
public:
    MNpc(CDefsTable*);
    ~MNpc();
    MTalk* getTalk();
    MItem* getGift();
    MAction* getKnowlege();
    std::string act();
    void onSpace();
    void update();
    bool learnSkill(MAction*);
};

#endif
