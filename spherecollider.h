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
     * @brief SphereCollider Constructor for BoxCollider class.
     * default role is 0 (neutral collider)
     * @param pc_ Vec2 position of the center of the disc
     * @param rc_ radius
     */
    SphereCollider(const Vec2 pc_, const float rc_);

    /**
     * SphereCollider Constructor for SphereCollider class.
     * @param pc_ Vec2  position of the center of the disc
     * @param rc_ float radius
     * @param role_ whether the sphere can destroy or heal the particles
     */
    SphereCollider(const Vec2 pc_, const float rc_, const int role_);


    /// Destructor for SphereCollider class.
    ~SphereCollider() override = default;

    /**
     * @brief check if collider particle is in contact with the spherical collider.
     * @param collider Particle to check position with
     * @return StaticConstraint corresponding to the sphere and the particle if in contact.
     */
    const std::optional<StaticConstraint> checkContact(Particle& collider) override;

    const Vec2 getPoint() const override;

    const float getRadius() const;


private:
    const Vec2 pc;    // Position of the center of the disc
    const float rc;   // Radius
};

#endif // SPHERECOLLIDER_H
