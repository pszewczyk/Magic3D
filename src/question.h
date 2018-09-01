#ifndef MQUESTION_H
#define MQUESTION_H

#include "interface.h"
#include "mortal.h"
#include "defstable.h"

class MQuestion {
private:
    string ask;
    string answer;
    string gift;
    string knowlege;
    string id;
public:
    MQuestion(string, CDefsTable*);
    ~MQuestion();
    string getAsk();
    string getAnswer();
    string getGift();
    string getKnowlege();
    bool end();
};

class MTalk : public MDrawable{
private:
    vector<MQuestion*> questions;
    vector<MText*> askSprites;
    string invitation;
    int chosenOne;
public:
    MTalk(CDefsTable*);
    vector<string> getAsks();
    void down();
    void up();
    void draw();
    string getCurrentAnswer();
    string getGiftString();
    string getKnowlegeString();
    string getInvitation();
    bool end();
};

#endif
