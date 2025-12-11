#ifndef PARTICLE_H
#define PARTICLE_H
#include "vec2.h"

class Particle
{
public:
    Particle(Vec2 pos, Vec2 velocity, float rad, float mass);

    Vec2 getPos();

    void setPos(Vec2 newPos);

    Vec2 getExpectedPos();

    void setExpectedPos(Vec2 newExpPos);

    float getX();

    float getY();

    Vec2 getVelocity();

    void setVelocity(Vec2 newVelocity);

private:
    Vec2 pos;
    Vec2 expectedPos;
    Vec2 velocity;
    float rad;
    float mass;
};

#endif // PARTICLE_H
