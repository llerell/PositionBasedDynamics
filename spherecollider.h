#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "collider.h"

class SphereCollider : public Collider
{
public:
    SphereCollider(Vec2 pc_, float rc_);

    ~SphereCollider() override = default;

    std::optional<StaticConstraint> checkContact(const Particle& collider) override;

    Vec2 getCenter() override;

    float getRadius();

private:
    Vec2 pc;
    float rc;
};

#endif // SPHERECOLLIDER_H
