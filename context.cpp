#include "context.h"
#include "plancollider.h"
#include "spherecollider.h"
#include <iostream>


Context::Context() {
    this->particles = std::vector<Particle>();
    this->colliders = std::vector<std::variant<PlanCollider,SphereCollider>>();
    this->staticConstraints = std::vector<StaticConstraint>();

    // Colliders
    PlanCollider groundCollider = PlanCollider(Vec2(0.0,1.0), Vec2(0.0,1.0));
    PlanCollider leftWall = PlanCollider(Vec2(0,0), Vec2(1,0.01));
    PlanCollider rightWall = PlanCollider(Vec2(15,0), Vec2(-1, -0.01));
    this->colliders.push_back(groundCollider);
    this->colliders.push_back(leftWall);
    this->colliders.push_back(rightWall);

    SphereCollider sphereCollider = SphereCollider(Vec2(2,3), 1.0);
    this->colliders.push_back(sphereCollider);
}

Vec2 solve(StaticConstraint sc)
{

    Vec2 qc = sc.part_ptr->getExpPos() - (((sc.part_ptr->getExpPos() - sc.pc).dotProduct(sc.nc))*sc.nc);
    Vec2 diff = sc.part_ptr->getExpPos() - qc;
    float C = diff.dotProduct(sc.nc) - sc.part_ptr->getRad();
    Vec2 delta = - C * sc.nc;
    return delta;
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

std::vector<StaticConstraint>& Context::getStaticConstraints() {
    return staticConstraints;
}

// Update the positions of the particles
void Context::updatePhysicalSystem(float dt) {
    applyExternalForce(dt);
    updateExpectedPosition(dt);
    addStaticContactConstraints();
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

void Context::addStaticContactConstraints() {
    staticConstraints.clear();
    for(int i=0; i<colliders.size(); i++) {
        for(int j=0; j<particles.size(); j++) {

            // variants and visitors as an alternative to inheritance
            using colliderVariant = std::variant<PlanCollider, SphereCollider>;
            colliderVariant coll_var = colliders[i];
            auto sc = std::visit([j, this](auto arg)->std::optional<StaticConstraint>{return arg.checkContact(this->particles[j]);}, coll_var);

            if (sc.has_value()){
                StaticConstraint sc_val = sc.value();
                staticConstraints.push_back(sc_val);
            }
        }
    }
}

void Context::addDynamicContactConstraints(float dt) {

}

void Context::projectConstraints() {
    std::vector<StaticConstraint>& staticConstraints = getStaticConstraints();
    for (int i=0; i<staticConstraints.size(); i++){
        Particle* part = staticConstraints[i].part_ptr;
        part->setExpPos(part->getExpPos()+solve(staticConstraints[i]));
    }
}

void Context::applyFriction(float dt) {

}

void Context::deleteContactConstraints() {

}




