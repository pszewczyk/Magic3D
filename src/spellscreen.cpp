#include "spellscreen.h"

MSpellScreen::MSpellScreen()
    : MWindow()
    , ContextAction(NULL)
{
    for(int i=0; i<12; i++) keynames[i] = IntToStr(i);
}

MSpellScreen::~MSpellScreen() {
}

bool MSpellScreen::learn(MAction* m) {
    slots.push_back(m);
    addDrawable(m->id, m->icon);
    m->icon->setVisible(true);
}

//bool MSpellScreen::pick(MAction*, int=10);
//bool MSpellScreen::unpick(MAction*);

bool MSpellScreen::forget(MAction* m) {
    for(int i=0; i<slots.size(); i++) if(slots[i]==m) {
        slots.erase(slots.begin()+i);
        rmDrawable(m->id);
    }
}

void MSpellScreen::draw() {
    int howmany = (Width)/33;
    for(int i=0; i<slots.size(); i++) {
        slots[i]->icon->setRect(X+33*(i%howmany)+10,Y+(33*((i)/howmany))+10, 32, 32);
        if(!ContextMenu && slots[i]->icon->hover(Gmachine->getCursorX(), Gmachine->getCursorY())) slots[i]->icon->setFocus(true);
        else slots[i]->icon->setFocus(false);
    }
    MWindow::draw();
}


std::string MSpellScreen::onClick() {
    if(ContextMenu) {
        for(int i=0; i<12; i++)
            if(ContextMenu->isDown(keynames[i])) {
            delete ContextMenu;
            ContextMenu = NULL;
            return keynames[i];
        }
    }
    delete ContextMenu;
    ContextMenu = NULL;
    return "nothing";
}

void MSpellScreen::showCMenu() {
    if(ContextMenu) {
        delete ContextMenu;
        ContextMenu=NULL;
    }
    ContextMenu = new MMenu("SpellsContextMenu", Gmachine->getCursorX(), Gmachine->getCursorY(), 150, 20);
    for(int i=0; i<slots.size(); i++)
        if(slots[i]->icon->hover(Gmachine->getCursorX(), Gmachine->getCursorY())) {
            printf("making context menu\n");
            for(int j=0; j<10; j++) ContextMenu->addButton(keynames[j], keynames[j]);
            ContextMenu->addButton(keynames[10], "LMB");
            ContextMenu->addButton(keynames[11], "RMB");
            ContextAction = slots[i];
            return;
        }
}

MAction* MSpellScreen::getContextAction() {
    return ContextAction;
}
