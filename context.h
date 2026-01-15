#ifndef CONTEXT_H
#define CONTEXT_H
#include "StaticConstraint.h"
#include "DynamicConstraint.h"
#include "collider.h"
#include "particle.h"
#include "plancollider.h"
#include "spherecollider.h"
#include <vector>
#include "vec2.h"
#include <cmath>
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

    std::vector<DynamicConstraint>& getDynamicConstraints();

    void updatePhysicalSystem(float dt);

    std::optional<DynamicConstraint> checkDynamicContact(Particle& part1, Particle& part2);

    void destroyParticles();

    void reset();

    void changeCollisions();

private:
    std::vector<Particle> particles;
    std::vector<std::variant<PlanCollider,SphereCollider>> colliders;
    //std::vector<PlanCollider> colliders;
    std::vector<StaticConstraint> staticConstraints;
    std::vector<DynamicConstraint> dynamicConstraints;
    bool collisions;

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
