#include "collider.h"

// Color depends on how the collider acts on particles
QColor neutralCol = Qt::black;
QColor killerCol = Qt::darkRed;
QColor healerCol = Qt::green;

Collider::Collider() : role(0), color(neutralCol) {}

Collider::Collider(int role_) : role(role_) {
    switch(role) {
    case 1:
        color = killerCol;
        break;
    case 2:
        color = healerCol;
        break;
    default:
        color = neutralCol;
    }
}

const int Collider::getRole() const {
    return role;
}

const QColor Collider::getColor() const {
    return color;
}
