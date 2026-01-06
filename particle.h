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


private:
    Vec2 pos;

    Vec2 expPos;

    Vec2 velocity;

    float rad;

    float mass;

    QColor color;
};

#endif // PARTICLE_H
