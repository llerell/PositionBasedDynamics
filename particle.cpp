#include "particle.h"

Particle::Particle(const Vec2 pos_, const Vec2 vel, const float rad_, const float mass_, const int health, const QColor initColor_)
    : pos(pos_), velocity(vel), rad(rad_), mass(mass_), expPos(pos_), initColor(initColor_), maxCollisions(health), color(initColor_), nbCollisions(0) {}

Particle::Particle()
    : pos(Vec2{0,0}), velocity(Vec2{0,0}), mass(0.0), rad(1.0), expPos(Vec2{0,0}), maxCollisions(50), color(Qt::gray), nbCollisions(0) {}

const Vec2 Particle::getPos() const {
    return pos;
}

void Particle::setPos(const Vec2 newPos) {
    this->pos = newPos;
}

const Vec2 Particle::getVelocity() const {
    return velocity;
}

void Particle::setVelocity(const Vec2 newVel){
  this->velocity=newVel;
}

const Vec2 Particle::getExpPos() const {
    return expPos;
}

void Particle::setExpPos(const Vec2 newExpPos) {
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
    const float coeff = float(nbCollisions)/float(maxCollisions);
    const int red = round(initColor.red()+coeff*(destrColor.red()-initColor.red()));
    const int green = round(initColor.green()+coeff*(destrColor.green()-initColor.green()));
    const int blue = round(initColor.blue()+coeff*(destrColor.blue()-initColor.blue()));
    color = QColor(red, green, blue);
}

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
