#ifndef PLANECOLLIDER_H
#define PLANECOLLIDER_H

#include "collider.h"
#include "vec2.h"

/**
 * PlaneCollider class
 * Line colliders to seperate scene in two halves : acceptable and not-acceptable.
 *
 */
class PlaneCollider : public Collider
{
public:
    /**
     * @brief Constructor for PlaneCollider class.
     * default role is 0 (neutral collider)
     * @param pc_ Point traversed by the plane
     * @param nc_ 2-Dimensional Normal Vector to the plane
     */
    PlaneCollider(const Vec2 pc_, const Vec2 nc_);

    /**
    * @brief Constructor for PlaneCollider.
    * @param pc_ Point traversed by the plane.
    * @param nc_ 2-Dimensional Normal Vector to the plane.
    * @param role_ whether the collider can destroy or heal the particles
    */
    PlaneCollider(const Vec2 pc_, const Vec2 nc_, const int role_);

    /// Destructor for PlaneCollider class.
    ~PlaneCollider() override {}

    /**
     * @brief check if collider particle is in contact with the plane collider.
     * If so, returns the corresponding StaticConstraint.
     * @param collider Particle to check
     * @return StaticConstraint corresponding to the plane and the particle if in contact.
     */
    const std::optional<StaticConstraint> checkContact(Particle& collider) override;

    const Vec2 getPoint() const override;

    const Vec2 getNormal() const ;

private:
    const Vec2 pc;    // A point of the plane
    const Vec2 nc;    // Normal vector
};

#endif // PLANECOLLIDER_H
