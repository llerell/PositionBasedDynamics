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
     * @brief Constructor for PlaneCollider class with parameters pc_ and nc_.
     * @param pc_ Point traversed by the plane
     * @param nc_ 2-Dimensional Normal Vector to the plane
     */
    PlaneCollider(Vec2 pc_, Vec2 nc_);

    /**
    * @brief Constructor for PlaneCollider class with parameters pc_, nc_ and isKiller_.
    * @param pc_ Point traversed by the plane.
    * @param nc_ 2-Dimensional Normal Vector to the plane.
    * @param isKiller_
    */
    PlaneCollider(Vec2 pc_, Vec2 nc_, bool isKiller_);

    /// Destructor for PlaneCollider class.
    ~PlaneCollider() override {}

    /**
     * @brief check if collider particle is in contact with the plane collider.
     * If so, returns the corresponding StaticConstraint.
     * @param collider Particle to check
     * @return StaticConstraint corresponding to the plane and the particle.
     */
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
