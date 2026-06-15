#ifndef PARTICLE_H
#define PARTICLE_H
#include "vec2.h"
#include <qcolor.h>

class Particle
{
public:
    /**
     * @brief Particle Constructor for Particle class.
     * @param pos 2D vector of the initial position
     * @param velocity 2D vector of the initial velocity
     * @param rad radius of the disc
     * @param mass mass of the particle
     * @param health initial number of health points
     * @param color_ initial color
     */
    Particle(const Vec2 pos, const Vec2 velocity, const float rad, const float mass, const int health, const QColor color_);

    /**
     * @brief Particle default constructor for a Particle
     * default position and velocity is (0,0)
     * default mass is 0 and default radius is 1.0
     * default health is 50
     * default color is gray
     */
    Particle();

    /// Destructor for Particle class
    ~Particle() = default;

    const Vec2 getPos() const ;

    void setPos(const Vec2 newPos);

    const Vec2 getVelocity() const ;

    void setVelocity(const Vec2 newVelocity);

    const Vec2 getExpPos() const;
  
    void setExpPos(const Vec2 newExpPos);

    const float getX() const ;

    const float getY() const ;

    const float getMass() const;

    const float getRad() const;

    const QColor getColor() const;

    /// Change the color depending on the number or health points left
    void updateColor();

    /// Add collision to the counter. Particles will get destroyed if the corresponding parameter is activated.
    void addCollision();

    /// Remove collision from the counter.
    void removeCollision();

   /**
     * @brief check number of collisions suffered by the particle compared to lifetime.
     * @return bool: whether the particles has suffered more collisions than maximum.
     */
    const bool checkNbCollisions() const;


private:
    Vec2 pos;

    Vec2 expPos;

    Vec2 velocity;

    float rad;

    float mass;

    /// initial color
    QColor initColor = QColor(200,200,200);
    /// color when the particle is one collision away from being destroyed
    QColor destrColor = QColor(255,0,0);
    /// current color of the particle
    QColor color;

    /// number of collisions suffered
    int nbCollisions;
    /// maximum health points
    int maxCollisions;
};

#endif // PARTICLE_H
