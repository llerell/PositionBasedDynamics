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

    virtual ~Collider() {}

    /**
     * @brief check if collider is in contact with the collider.
     * If so, returns the corresponding StaticConstraint.
     * @param collider Particle to check
     * @return StaticConstraint corresponding to the plane and the particle.
     */
    virtual auto checkContact(Particle& collider)-> std::optional<StaticConstraint> =0;

    virtual Vec2 getCenter() = 0;

private:
};

#endif // COLLIDER_H
