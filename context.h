#ifndef CONTEXT_H
#define CONTEXT_H
#include "StaticConstraint.h"
#include "DynamicConstraint.h"
#include "collider.h"
#include "particle.h"
#include "planecollider.h"
#include "spherecollider.h"
#include "boxcollider.h"
#include <vector>
#include "vec2.h"
#include <cmath>

class Context
{
public:
    Context();

    /// push new Particle to the vector
    void addParticle(Particle particle);

    /// get number of Particles present in the current context
    const int getNbParticles() const;

    /// return std::vector of all particles listed in the context.
    const std::vector<Particle>& getParticles() const;

    /// return std::vector of Colliders, whether Plane, Spherical, of Rectangular, using std::variant.
    const auto getColliders() const -> std::vector<std::variant<PlaneCollider, SphereCollider, BoxCollider>>;

    /// return std::vector of all StaticConstraints between obstacles and particles.
    std::vector<StaticConstraint>& getStaticConstraints() ;

    /// return std::vector of all DynamicConstraints between particles.
    std::vector<DynamicConstraint>& getDynamicConstraints() ;

    /// updates all particles and their attributes for the next iteration.
    void updatePhysicalSystem(float dt);

    /**
     * @brief Check if input part1 and part2 are in contact according to their expected positions
     * and return DynamicConstraint if so.
     * @param part1, part2 Particle& input
     * @returns std::optional value containing DynamicContact if contact is detected.
     */
    std::optional<DynamicConstraint> checkDynamicContact(Particle& part1, Particle& part2);

    /// Destroys particles after too many collisions.
    void destroyParticles();

    /// Reset the context (remove all particles).
    void reset();

    const bool getCollisionsToggle() const ;
    void changeCollisions();

private:
    std::vector<Particle> particles;
    std::vector<std::variant<PlaneCollider,SphereCollider, BoxCollider>> colliders;
    std::vector<StaticConstraint> staticConstraints;
    std::vector<DynamicConstraint> dynamicConstraints;
    bool collisions;

    /// Sets velocity of each particle according to external forces implemented herein.
    void applyExternalForce(float dt);

    /// For each particle, sets position to new expected position and velocity to the difference between current position and previous position.
    void updateVelocityAndPosition(float dt);

    /// Sets expected position of each particle according to its velocity.
    void updateExpectedPosition(float dt);

    /// Add contact constraints between particles when expected positions make them overlap.
    void addDynamicContactConstraints();

    /**
     * @brief Add contact constraints between particles and static environment obstacles when expected positions make them overlap,
     * e.g. Box colliders and spherical colliders.
     */
    void addStaticContactConstraints();

    /// Calculate new positions of each particle according to all constraints.
    void projectConstraints();

    /// Calculate friction applied to each particle and updates its velocity accordingly.
    void applyFriction(float dt);

    /// delete all contact constraints from the context, both static and dynamic.
    void deleteContactConstraints();

};

#endif // CONTEXT_H
