#include "context.h"
#include "plancollider.h"
#include "spherecollider.h"

Context::Context() {
    this->particles = std::vector<Particle>();
    this->colliders = std::vector<std::variant<PlanCollider,SphereCollider>>();
    //this->colliders = std::vector<PlanCollider>();
    this->staticConstraints = std::vector<StaticConstraint>();
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
    staticConstraints.clear();
    for(int i=0; i<colliders.size(); i++) {
        for(int j=0; j<particles.size(); j++) {
            std::optional<StaticConstraint>* p_sc;

            std::variant<PlanCollider, SphereCollider> coll_var = colliders[i];
            std::visit([j, p_sc, this](auto& arg) {*p_sc=arg.checkContact(this->particles[j]);}, coll_var);
            //if (p_sc->has_value()){
                //StaticConstraint sc = p_sc->value();
                //staticConstraints.push_back(sc);
                //Vec2 d = delta(sc);
                //particles[i].setPos(particles[i].getExpPos()+d);
            //}

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

Vec2 delta(StaticConstraint sc)
{

    Vec2 qc = sc.part_ptr->getExpPos() + (-1) * sc.nc*sc.nc.dotProduct(sc.part_ptr->getExpPos()+(-1)*sc.pc);
    Vec2 diff = sc.part_ptr->getExpPos() + (-1) * qc;
    float C = diff.dotProduct(sc.nc) - sc.part_ptr->getRad();
    return -C * sc.nc;
}


