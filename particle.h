#ifndef PARTICLE_H
#define PARTICLE_H
#include "vec2.h"
#include <qcolor.h>

class Particle
{
public:
    Particle(Vec2 pos, Vec2 velocity, float rad, float mass, QColor color_);

    Particle();

    const Vec2 getPos();

    void setPos(Vec2 newPos);

    const Vec2 getVelocity();

    void setVelocity(Vec2 newVelocity);

    const Vec2 getExpPos() const;
  
    void setExpPos(Vec2 newExpPos);

    const float getX();

    const float getY();

    const float getMass();

    const float getRad() const;

    const QColor getColor() const;

    void updateColor();

    // Destruction after too many dynamic collisions
    void addCollision();

    void removeCollision();

    bool checkNbCollisions();


private:
    Vec2 pos;

    Vec2 expPos;

    Vec2 velocity;

    float rad;

    float mass;

    QColor initColor = QColor(200,200,200);

    QColor destrColor = QColor(255,0,0);

    QColor color;

    // Destruction after too many dynamic collisions
    int nbCollisions;

    int maxCollisions = 50;
};

#endif // PARTICLE_H
