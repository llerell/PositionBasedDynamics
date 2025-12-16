#ifndef COLLIDER_H
#define COLLIDER_H

#include "StaticConstraint.h"
#include "particle.h"
#include <optional>
#include <qpainter.h>

// Abstract class that defines colliders objects
class Collider
{
public:
    Collider();

    virtual ~Collider() {}

    virtual auto checkContact(const Particle& collider)-> std::optional<StaticConstraint> =0;

    virtual Vec2 getCenter()=0;

private:
};

#endif // COLLIDER_H
