#include "collider.h"

// Color depends on how the collider acts on particles
QColor neutralCol = Qt::black;
QColor killerCol = Qt::darkRed;
QColor healerCol = Qt::green;

Collider::Collider() : isKiller(false), isHealer(false), color(neutralCol) {}

Collider::Collider(bool isKiller_, bool isHealer_) : isKiller(isKiller_), isHealer(isHealer_) {
    if(isHealer_) {
        color = healerCol;
    }
    else if(isKiller_) {
        color = killerCol;
    }
    else {
        color = neutralCol;
    }
}

bool Collider::canDestroy() {
    return isKiller;
}

bool Collider::canHeal() {
    return isHealer;
}

QColor Collider::getColor() {
    return color;
}
