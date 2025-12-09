#include "particle.h"

Particle::Particle(Vec2 pos_, Vec2 vel, float rad_, float mass_)
    : pos(pos_), velocity(vel), rad(rad_), mass(mass_) {}

Vec2& Particle::getPos() {
    return pos;
}

float Particle::getX() {
    return pos.getX();
}

float Particle::getY() {
    return pos.getY();
}

void Particle::setPos(Vec2 newPos) {
    this->pos = newPos;
}
