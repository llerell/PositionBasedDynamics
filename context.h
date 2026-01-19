#ifndef CONTEXT_H
#define CONTEXT_H
#include "StaticConstraint.h"
#include "DynamicConstraint.h"
#include "particle.h"
#include "planecollider.h"
#include "spherecollider.h"
#include "boxcollider.h"
#include <vector>
#include <cmath>

class Context
{
public:
    Context();

    /// push new Particle to the vector
    void addParticle(const Particle particle);

    /// get number of Particles present in the current context
    const int getNbParticles() const;

    /// return std::vector of all particles listed in the context.
    const std::vector<Particle>& getParticles() const;

    /**
     * @brief getColliders
     * @return std::vector of Colliders, whether Plane, Spherical, of Rectangular, using std::variant.
     */
    const std::vector<std::variant<PlaneCollider, SphereCollider, BoxCollider>> getColliders() const;

    /// get whether the particles can be destroyed.
    const bool getCollisionsToggle() const ;

    /// updates all particles and their attributes for the next iteration.
    void updatePhysicalSystem(const float dt);

    /// Destroys particles after too many collisions.
    void destroyParticles();

    /// Reset the context (remove all particles).
    void reset();

    /// Active or desactive the destruction of the particles.
    void changeCollisions();

private:
    std::vector<Particle> particles;
    std::vector<std::variant<PlaneCollider,SphereCollider, BoxCollider>> colliders;
    std::vector<StaticConstraint> staticConstraints;
    std::vector<DynamicConstraint> dynamicConstraints;
    bool collisions;

    /// Sets velocity of each particle according to external forces implemented herein.
    void applyExternalForce(const float dt);

    /// For each particle, sets position to new expected position and velocity to the difference between current position and previous position.
    void updateVelocityAndPosition(const float dt);

    /// Sets expected position of each particle according to its velocity.
    void updateExpectedPosition(const float dt);

    /**
     * @brief Add contact constraints between particles and static environment obstacles when expected positions make them overlap,
     * e.g. Box colliders and spherical colliders.
     */
    void addStaticContactConstraints();

    /// Add contact constraints between particles when expected positions make them overlap.
    void addDynamicContactConstraints();

    /**
     * @brief Check if input part1 and part2 are in contact according to their expected positions
     * and return DynamicConstraint if so.
     * @param part1, part2 Particle& input
     * @returns std::optional value containing DynamicContact if contact is detected.
     */
    const std::optional<DynamicConstraint> checkDynamicContact(Particle& part1, Particle& part2);

    /// Calculate new positions of each particle according to all constraints.
    void projectConstraints();

    /// Calculate friction applied to each particle and updates its velocity accordingly.
    void applyFriction(const float dt);

    /// delete all contact constraints from the context, both static and dynamic.
    void deleteContactConstraints();

};

#endif // CONTEXT_H
