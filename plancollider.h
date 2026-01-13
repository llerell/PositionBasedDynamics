#ifndef PLANCOLLIDER_H
#define PLANCOLLIDER_H

#include "collider.h"
#include "vec2.h"

class PlanCollider : public Collider
{
public:
    PlanCollider(Vec2 pc_, Vec2 nc_);

    PlanCollider(Vec2 pc_, Vec2 nc_, bool isKiller_);

    ~PlanCollider() override {}

    std::optional<StaticConstraint> checkContact(Particle& collider) override;

    Vec2 getCenter() override;

    Vec2 getNormal();

    bool canDestroy();

private:
    Vec2 pc;    // A point of the plane
    Vec2 nc;    // Normal vector

    bool isKiller;  // If the collider can destroy the particles
};

#endif // PLANCOLLIDER_H
