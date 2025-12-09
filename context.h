#ifndef CONTEXT_H
#define CONTEXT_H
#include "particle.h"
#include <vector>

class Context
{
public:
    Context();

    void addParticle(Particle particle);

    int getNbParticles();

    std::vector<Particle>& getParticles();

    void updatePhysicalSystem(float dt);

private:
    std::vector<Particle> particles;

    void applyExternalForce(float dt);
    void dampVelocities(float dt);
    void updateExpectedPosition(float dt);
    void addDynamicContactConstraints(float dt);
    void addStaticContactConstraints(float dt);
    void projectConstraints();
    void applyFriction(float dt);
    void deleteContactConstraints();

};

#endif // CONTEXT_H
