#ifndef COLLIDER_H
#define COLLIDER_H

#include "StaticConstraint.h"
#include "particle.h"
#include <optional>


// Abstract class that defines colliders objects
class Collider
{
public:
    Collider();
    Collider(int role_);

    virtual ~Collider() {}

    /**
     * @brief check if collider is in contact with the collider.
     * If so, returns the corresponding StaticConstraint.
     * @param collider Particle to check
     * @return StaticConstraint corresponding to the plane and the particle.
     */
    virtual auto checkContact(Particle& collider)-> std::optional<StaticConstraint> =0;

    virtual const Vec2 getPoint() const = 0;

    const int getRole() const;

    const QColor getColor() const;

protected:
    const int role;   // 0 if the collider does nothing, 1 if it can destroy the particles, 2 if it can heal them
    QColor color;
};

#endif // COLLIDER_H
