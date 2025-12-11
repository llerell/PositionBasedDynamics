#ifndef PARTICLE_H
#define PARTICLE_H
#include "vec2.h"

class Particle
{
public:
    Particle(Vec2 pos, Vec2 velocity, float rad, float mass);

    Vec2& getPos();

    Vec2& getVelocity();

    Vec2& getExpPos();

    float getX();

    float getY();

    float getMass();

    void setPos(Vec2 newPos);

private:
    Vec2 pos;
    Vec2 velocity;
    float rad;
    float mass;
    Vec2 expPos;
};

#endif // PARTICLE_H
