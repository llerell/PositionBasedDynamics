#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#include "collider.h"
#include "vec2.h"

class PlaneCollider : public Collider
{
public:
    PlaneCollider(Vec2 pc_, Vec2 nc_);

    PlaneCollider(Vec2 pc_, Vec2 nc_, bool isKiller_);

    ~PlaneCollider() override {}

    std::optional<StaticConstraint> checkContact(Particle& collider) override;

    Vec2 getCenter() override;

    Vec2 getNormal();

    bool canDestroy();

private:
    Vec2 pc;    // A point of the plane
    Vec2 nc;    // Normal vector

    bool isKiller;  // If the collider can destroy the particles
};

#endif // PLANECOLLIDER_H
