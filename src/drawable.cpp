#include "drawable.h"

MDrawable::MDrawable()
    : Visible(true)
    , X(0)
    , Y(0)
    , Width(0)
    , Height(0)
{
}

MDrawable::~MDrawable() {
    setVisible(false);
}


bool MDrawable::getVisible() {
    return Visible;
}

void MDrawable::setVisible(bool visible) {
    Visible = visible;
}

void MDrawable::setPos(int x, int y) {
    X = x;
    Y = y;
}

void MDrawable::setRect(int x, int y, int w, int h) {
    X = x;
    Y = y;
    Width = w;
    Height = h;
}

void MDrawable::Translate(int x, int y) {
    X += x;
    Y += y;
}
