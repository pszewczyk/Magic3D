#ifndef MQUESTION_H
#define MQUESTION_H

#include "interface.h"
#include "mortal.h"
#include "defstable.h"

class MQuestion {
private:
    std::string ask;
    std::string answer;
    std::string gift;
    std::string knowlege;
    std::string id;
public:
    MQuestion(std::string, CDefsTable*);
    ~MQuestion();
    std::string getAsk();
    std::string getAnswer();
    std::string getGift();
    std::string getKnowlege();
    bool end();
};

class MTalk : public MDrawable{
private:
    std::vector<MQuestion*> questions;
    std::vector<MText*> askSprites;
    std::string invitation;
    int chosenOne;
public:
    MTalk(CDefsTable*);
    std::vector<std::string> getAsks();
    void down();
    void up();
    void draw();
    std::string getCurrentAnswer();
    std::string getGiftString();
    std::string getKnowlegeString();
    std::string getInvitation();
    bool end();
};

#endif
