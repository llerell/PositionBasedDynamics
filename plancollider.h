#ifndef PLANCOLLIDER_H
#define PLANCOLLIDER_H

#include "collider.h"

class PlanCollider : public Collider
{
public:
    PlanCollider(Vec2 pc_, Vec2 nc_);

    ~PlanCollider() override {}

    std::optional<StaticConstraint> checkContact(const Particle& collider) override;

    Vec2 getCenter() override;

    Vec2 getNormal();

private:
    Vec2 pc;    // A point of the plan
    Vec2 nc;    // Normal vector
};

#endif // PLANCOLLIDER_H
