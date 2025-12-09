#include "context.h"

Context::Context() {
    this->particles = std::vector<Particle>();
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

// Update the positions of the particles
// For now only make them fall independantly of the particle
void Context::updatePhysicalSystem(float dt) {
    for(int i=0; i<particles.size(); i++) {
        Particle& part = particles[i];
        Vec2& pos = part.getPos();
        float& y = pos.getY();
        y += 5;
    }
}


void Context::applyExternalForce(float dt) {

}

void Context::dampVelocities(float dt) {

}

void Context::updateExpectedPosition(float dt) {

}

void Context::addDynamicContactConstraints(float dt) {

}

void Context::addStaticContactConstraints(float dt) {

}

void Context::projectConstraints() {

}

void Context::applyFriction(float dt) {

}

void Context::deleteContactConstraints() {

}

