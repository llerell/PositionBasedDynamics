#include "context.h"
#include "plancollider.h"
#include "spherecollider.h"

Context::Context() {
    this->particles = std::vector<Particle>();
    this->colliders = std::vector<std::variant<PlanCollider,SphereCollider>>();
    //this->colliders = std::vector<PlanCollider>();
    this->staticConstraints = std::vector<StaticConstraint>();
    this->dynamicConstraints = std::vector<DynamicConstraint>();
    // Colliders for tests
    PlanCollider planCollider = PlanCollider(Vec2(7,1), Vec2(0.5,10));
    this->colliders.push_back(planCollider);
    SphereCollider sphereCollider = SphereCollider(Vec2(2,3), 2.0);
    this->colliders.push_back(sphereCollider);
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

std::vector<std::variant<PlanCollider,SphereCollider>>& Context::getColliders() {
    return colliders;
}

//std::vector<PlanCollider>& Context::getColliders() {
//    return colliders;
//}

std::vector<StaticConstraint>& Context::getStaticConstraints() {
    return staticConstraints;
}

std::vector<DynamicConstraint>& Context::getDynamicConstraints() {
    return dynamicConstraints;
}

std::optional<DynamicConstraint> Context::checkDynamicContact(Particle& part1, Particle& part2) {
    Vec2 p1 = part1.getExpPos();
    Vec2 p2 = part2.getExpPos();
    float r1 = part1.getRad();
    float r2 = part2.getRad();
    float d = (p1-p2).length();
    if((r1+r2)-d>0) {
        return DynamicConstraint {&part1, &part2};
    }
    else {
        return {};
    }
}

// Update the positions of the particles
void Context::updatePhysicalSystem(float dt) {
    applyExternalForce(dt);
    updateExpectedPosition(dt);
    addStaticContactConstraints(dt);
    addDynamicContactConstraints(dt);
    projectConstraints();
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

            //std::optional<StaticConstraint> sc = colliders[i].checkContact(particles[j]);
        }
    }
}

void Context::addDynamicContactConstraints(float dt) {
    dynamicConstraints.clear();
    for(int i=0; i<particles.size(); i++) {
        for(int j=i+1; j<particles.size(); j++) {
            std::optional<DynamicConstraint> dc = checkDynamicContact(particles[i], particles[j]);
            if(dc.has_value()) {
                dynamicConstraints.push_back(dc.value());
            }
        }
    }
}

void Context::projectConstraints() {
    // Static constraints
    // ...

    // Dynamic constraints
    for(int i=0; i<dynamicConstraints.size(); i++) {
        dynamicConstraints[i].enforceDynamicConstraint();
    }
}

void Context::applyFriction(float dt) {

}

void Context::deleteContactConstraints() {

}

