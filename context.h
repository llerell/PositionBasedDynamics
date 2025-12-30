#ifndef CONTEXT_H
#define CONTEXT_H
#include "StaticConstraint.h"
#include "collider.h"
#include "particle.h"
#include "plancollider.h"
#include "spherecollider.h"
#include <vector>
#include "vec2.h"

class Context
{
public:
    Context();

    void addParticle(Particle particle);

    int getNbParticles();

    std::vector<Particle>& getParticles();

    std::vector<std::variant<PlanCollider, SphereCollider>>& getColliders();
    //std::vector<PlanCollider>& getColliders();

    std::vector<StaticConstraint>& getStaticConstraints();

    void updatePhysicalSystem(float dt);

private:
    std::vector<Particle> particles;
    std::vector<std::variant<PlanCollider,SphereCollider>> colliders;
    //std::vector<PlanCollider> colliders;
    std::vector<StaticConstraint> staticConstraints;

    void applyExternalForce(float dt);
    void updateVelocityAndPosition(float dt);
    void updateExpectedPosition(float dt);
    void dampVelocities(float dt);
    void addDynamicContactConstraints(float dt);
    void addStaticContactConstraints();
    void projectConstraints();
    void applyFriction(float dt);
    void deleteContactConstraints();

};
Vec2 solve(StaticConstraint sc);
#endif // CONTEXT_H
