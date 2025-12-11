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
void Context::updatePhysicalSystem(float dt) {
    applyExternalForce(dt);
    updateExpectedPosition(dt);
    updateVelocityAndPosition(dt);
}


void Context::applyExternalForce(float dt) {
    // Gravity
    float m;
    float g = 9.81;
    for(int i=0; i<particles.size(); i++) {
        m = particles[i].getMass();
        Vec2 Fg = Vec2(0,m*g);

        particles[i].getVelocity() = particles[i].getVelocity() + Fg * (dt/m);
    }

}

void Context::updateExpectedPosition(float dt) {
    for(int i=0; i<particles.size(); i++) {
        particles[i].getExpPos() = particles[i].getPos() + particles[i].getVelocity() * dt;
    }
}

void Context::updateVelocityAndPosition(float dt) {
    for(int i=0; i<particles.size(); i++) {
        particles[i].getVelocity() = particles[i].getExpPos() - particles[i].getPos();
        particles[i].getPos() = particles[i].getExpPos();
    }
}

void Context::dampVelocities(float dt) {

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

