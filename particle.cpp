#include "particle.h"

Particle::Particle(Vec2 pos_, Vec2 vel, float rad_, float mass_)
    : pos(pos_), expectedPos(pos_), velocity(vel), rad(rad_), mass(mass_) {}

Vec2 Particle::getPos() {
    return pos;
}

void Particle::setPos(Vec2 newPos) {
    this->pos = newPos;
}

Vec2 Particle::getExpectedPos() {
    return expectedPos;
}

void Particle::setExpectedPos(Vec2 newExpPos) {
    this->expectedPos = newExpPos;
}

float Particle::getX() {
    return pos.getX();
}

float Particle::getY() {
    return pos.getY();
}

Vec2 Particle::getVelocity(){
    return velocity;
}

void Particle::setVelocity(Vec2 newVel){
    this->velocity = newVel;
}
