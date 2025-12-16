#ifndef CONTEXT_H
#define CONTEXT_H
#include "StaticConstraint.h"
#include "plancollider.h"
#include "particle.h"
#include <vector>

class Context
{
public:
    Context();

    void addParticle(Particle particle);

    int getNbParticles();

    std::vector<Particle>& getParticles();

    std::vector<PlanCollider>& getColliders();

    std::vector<StaticConstraint>& getStaticConstraints();

    void updatePhysicalSystem(float dt);

private:
    std::vector<Particle> particles;
    std::vector<PlanCollider> colliders;
    std::vector<StaticConstraint> staticConstraints;

    void applyExternalForce(float dt);
    void updateVelocityAndPosition(float dt);
    void updateExpectedPosition(float dt);
    void dampVelocities(float dt);
    void addDynamicContactConstraints(float dt);
    void addStaticContactConstraints(float dt);
    void projectConstraints();
    void applyFriction(float dt);
    void deleteContactConstraints();

};

#endif // CONTEXT_H
