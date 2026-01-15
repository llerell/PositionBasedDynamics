#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "collider.h"
#include "vec2.h"

class SphereCollider : public Collider
{
public:
    SphereCollider(Vec2 pc_, float rc_);

    SphereCollider(Vec2 pc_, float rc_, bool isKiller_);

    ~SphereCollider() override = default;

    std::optional<StaticConstraint> checkContact(Particle& collider) override;

    Vec2 getCenter() override;

    float getRadius();

    bool canDestroy();

private:
    Vec2 pc;
    float rc;

    bool isKiller;  // If the collider can destroy the particles
};

#endif // SPHERECOLLIDER_H
