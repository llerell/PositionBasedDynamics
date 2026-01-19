#include "particle.h"

Particle::Particle(Vec2 pos_, Vec2 vel, float rad_, float mass_, int health, QColor initColor_)
    : pos(pos_), velocity(vel), rad(rad_), mass(mass_), expPos(pos_), initColor(initColor_), maxCollisions(health), color(initColor_), nbCollisions(0) {}

Particle::Particle(): pos(Vec2{0,0}), velocity(Vec2{0,0}), mass(0.0), expPos(Vec2{0,0}), maxCollisions(50), color(Qt::gray), nbCollisions(0) {}

const Vec2 Particle::getPos() const {
    return pos;
}

void Particle::setPos(Vec2 newPos) {
    this->pos = newPos;
}

const Vec2 Particle::getVelocity() const {
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

const float Particle::getX() const {
    return pos.getX();
}

const float Particle::getY() const {
    return pos.getY();
}

const float Particle::getMass() const {
    return mass;
}

const float Particle::getRad() const {
    return rad;
}

const QColor Particle::getColor() const {
    return color;
}

void Particle::updateColor() {
    // Color depending on the number of collisions
    float coeff = float(nbCollisions)/float(maxCollisions);
    int red = round(initColor.red()+coeff*(destrColor.red()-initColor.red()));
    int green = round(initColor.green()+coeff*(destrColor.green()-initColor.green()));
    int blue = round(initColor.blue()+coeff*(destrColor.blue()-initColor.blue()));
    color = QColor(red, green, blue);
}

// Destruction after too many dynamic collisions
void Particle::addCollision() {
    nbCollisions++;
    updateColor();
}

void Particle::removeCollision() {
    nbCollisions = std::max(0, nbCollisions-2);
    updateColor();
}

const bool Particle::checkNbCollisions() const{
    return nbCollisions > maxCollisions;
}
