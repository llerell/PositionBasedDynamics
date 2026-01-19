#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "collider.h"
#include "vec2.h"

/**
 * SphereCollider class.
 * Disc obstacle represented by the position of its center and its radius.
 *
 */
class SphereCollider : public Collider
{
public:
    /**
     * SphereCollider Constructor for SphereCollider class with params pc_ and rc_.
     *
     * @param pc_ Vec2 position of the center of the disc
     * @param rc_ radius
     */
    SphereCollider(Vec2 pc_, float rc_);

    /**
     * SphereCollider Constructor for SphereCollider class with params pc_, rc_, isKiller_.
     * @param pc_ Vec2  position of the center of the disc
     * @param rc_ float radius
     * @param isKiller_ boolean representing whether the sphere deals damage to particles.
     */
    SphereCollider(Vec2 pc_, float rc_, int role_);


    /// Destructor for SphereCollider class.
    ~SphereCollider() override = default;

    /**
     * @brief check if collider particle is in contact with the spherical collider.
     * @param collider Particle to check position with
     * @return StaticConstraint corresponding to the sphere and the particle if in contact.
     */
    std::optional<StaticConstraint> checkContact(Particle& collider) override;

    const Vec2 getPoint() const override;

    const float getRadius() const;


private:
    Vec2 pc;

    float rc;
};

#endif // SPHERECOLLIDER_H
