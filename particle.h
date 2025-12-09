#ifndef PARTICLE_H
#define PARTICLE_H
#include "vec2.h"

class Particle
{
public:
    Particle(Vec2 pos, Vec2 velocity, float rad, float mass);

    Vec2& getPos();

    float getX();

    float getY();

    void setPos(Vec2 newPos);

private:
    Vec2 pos;
    Vec2 velocity;
    float rad;
    float mass;
};

#endif // PARTICLE_H
