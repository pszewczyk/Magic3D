#include "question.h"

MQuestion::MQuestion(std::string d, CDefsTable* defs)
    : ask(defs->GetString("ask","Nie wiem o co spytaæ."))
    , answer(defs->GetString("answer","Nie wiem co odpowiedzieæ"))
    , gift(defs->GetString("gift","nothing"))
    , knowlege(defs->GetString("knowlege","nothing"))
    , id(d)
{
}

std::string MQuestion::getAsk() {
    return ask;
}

std::string MQuestion::getAnswer() {
    return answer;
}

std::string MQuestion::getGift() {
    return gift;
}

std::string MQuestion::getKnowlege() {
    return knowlege;
}

bool MQuestion::end() {
    return id=="end";
}


MTalk::MTalk(CDefsTable* defs)
    : invitation(defs->GetString("invitation", "nie wiem jak ciê przywitaæ"))
    , chosenOne(0)
{
    std::vector<std::string> vals = defs->GetTabeleK();
    
    questions.clear();
    for(int i=0; i<vals.size(); i++){
        questions.push_back(new MQuestion(vals[i], defs->GetTable(vals[i])));
        askSprites.push_back(new MText(Gmachine->getWidth()/2-100, Gmachine->getHeight()-25*(i+1), questions[i]->getAsk()));
    }
}

std::vector<std::string> MTalk::getAsks() {
    std::vector<std::string> result;
    for(int i=0; i<questions.size(); i++)
        result.push_back(questions[i]->getAsk());
    return result;
}

void MTalk::draw() {
    for(int i=0; i<askSprites.size(); i++) askSprites[i]->setColor(255,255,255,255);
    askSprites[chosenOne]->setColor(255,255,200,100);
    for(int i=0; i<askSprites.size(); i++) askSprites[i]->draw();
}

void MTalk::down() {
    chosenOne--;
    chosenOne%=askSprites.size();
}

void MTalk::up() {
    chosenOne++;
    chosenOne%=askSprites.size();
}

std::string MTalk::getCurrentAnswer() {
    return questions[chosenOne]->getAnswer();
}

std::string MTalk::getInvitation() {
    return invitation;
}

std::string MTalk::getGiftString() {
    return questions[chosenOne]->getGift();
}

std::string MTalk::getKnowlegeString() {
    return questions[chosenOne]->getKnowlege();
}

bool MTalk::end() {
    return questions[chosenOne]->end();
}
