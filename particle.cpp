#include "particle.h"

Particle::Particle(Vec2 pos_, Vec2 vel, float rad_, float mass_)
    : pos(pos_), velocity(vel), rad(rad_), mass(mass_), expPos(pos_) {}

const Vec2 Particle::getPos() {
    return pos;
}

void Particle::setPos(Vec2 newPos) {
    this->pos = newPos;
}

const Vec2 Particle::getVelocity() {
    return velocity;
}

void Particle::setVelocity(Vec2 newVel){
  this->velocity=newVel;
}

const Vec2 Particle::getExpPos() const {
    return expPos;
}

void Particle::setExpPos(Vec2 newExpPos) {
    this-> expPos = newExpPos;
}

const float Particle::getX() {
    return pos.getX();
}

const float Particle::getY() {
    return pos.getY();
}

const float Particle::getMass() {
    return mass;
}

const float Particle::getRad() const {
    return rad;
}
