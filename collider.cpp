#include "collider.h"

// Color depends on how the collider acts on particles
QColor neutralCol = Qt::black;
QColor killerCol = Qt::darkRed;
QColor healerCol = Qt::green;

Collider::Collider() : isKiller(false), isHealer(false), color(neutralCol) {}

Collider::Collider(bool isKiller_, bool isHealer_) : isKiller(isKiller_), isHealer(isHealer_) {
    if(isKiller_) {
        if(isHealer_) {
            color = neutralCol;
        }
        else {
            color = killerCol;
        }
    }
    else if(isHealer_) {
        color = healerCol;
    }
    else {
        color = neutralCol;
    }
}

const bool Collider::canDestroy() const {
    return isKiller;
}

const bool Collider::canHeal() const {
    return isHealer;
}

const QColor Collider::getColor() const {
    return color;
}
