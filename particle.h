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

    /// Add collision to the counter. Particles will get destroyed if the corresponding parameter is activated.
    void addCollision();

    /**
     * @brief check number of collisions suffered by the particle compared to lifetime.
     * @return bool: whether the particles has suffered more collisions than maximum.
     */
    bool checkNbCollisions();


private:
    Vec2 pos;

    Vec2 expPos;

    Vec2 velocity;

    float rad;

    float mass;

    QColor color;

    // Destruction after too many dynamic collisions
    int nbCollisions;

    int maxCollisions = 50;
};

#endif // PARTICLE_H
