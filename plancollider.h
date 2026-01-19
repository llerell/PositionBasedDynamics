#ifndef PLANCOLLIDER_H
#define PLANCOLLIDER_H

#include "collider.h"
#include "vec2.h"

class PlanCollider : public Collider
{
public:
    PlanCollider(Vec2 pc_, Vec2 nc_);

    PlanCollider(Vec2 pc_, Vec2 nc_, bool isKiller_, bool is_Healer_);

    ~PlanCollider() override {}

    std::optional<StaticConstraint> checkContact(Particle& collider) override;

    Vec2 getPoint() override;

    Vec2 getNormal();

private:
    Vec2 pc;    // A point of the plane
    Vec2 nc;    // Normal vector
};

#endif // PLANCOLLIDER_H
