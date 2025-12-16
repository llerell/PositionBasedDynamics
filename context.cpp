#include "context.h"
#include "plancollider.h"

Context::Context() {
    this->particles = std::vector<Particle>();
    this->colliders = std::vector<PlanCollider>();
    this->staticConstraints = std::vector<StaticConstraint>();
    // PlanCollider for tests
    PlanCollider planCollider = PlanCollider(Vec2(0,10), Vec2(1,0));
    this->colliders.push_back(planCollider);
}

void Context::addParticle(Particle particle) {
    this->particles.push_back(particle);
}

int Context::getNbParticles() {
    return particles.size();
}

std::vector<Particle>& Context::getParticles() {
    return particles;
}

std::vector<PlanCollider>& Context::getColliders() {
    return colliders;
}

std::vector<StaticConstraint>& Context::getStaticConstraints() {
    return staticConstraints;
}

// Update the positions of the particles
void Context::updatePhysicalSystem(float dt) {
    applyExternalForce(dt);
    updateExpectedPosition(dt);
    addStaticContactConstraints(dt);
    updateVelocityAndPosition(dt);
}


void Context::applyExternalForce(float dt) {
    // Gravity
    float m;
    float g = 9.81;
    for(int i=0; i<particles.size(); i++) {
        m = particles[i].getMass();
        const Vec2 Fg = Vec2(0,-m*g);

        particles[i].setVelocity(particles[i].getVelocity() + Fg * (dt/m));
    }

}

void Context::updateExpectedPosition(float dt) {
    for(int i=0; i<particles.size(); i++) {
        particles[i].setExpPos(particles[i].getPos() + particles[i].getVelocity() * dt);
    }
}

void Context::updateVelocityAndPosition(float dt) {
    for(int i=0; i<particles.size(); i++) {
        particles[i].setVelocity((particles[i].getExpPos() - particles[i].getPos())*(1/dt));
        particles[i].setPos(particles[i].getExpPos());
    }
}

void Context::dampVelocities(float dt) {

}

void Context::addStaticContactConstraints(float dt) {
    for(int i=0; i<colliders.size(); i++) {
        for(int j=0; j<particles.size(); j++) {


            //this->staticConstraints.push_back(colliders[i].checkContact(particles[j]));
        }
    }
}

void Context::addDynamicContactConstraints(float dt) {

}

void Context::projectConstraints() {

}

void Context::applyFriction(float dt) {

}

void Context::deleteContactConstraints() {

}

