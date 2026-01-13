#include "context.h"


Context::Context() {
    this->particles = std::vector<Particle>();
    this->colliders = std::vector<std::variant<PlanCollider,SphereCollider, BoxCollider>>();
    this->staticConstraints = std::vector<StaticConstraint>();
    this->dynamicConstraints = std::vector<DynamicConstraint>();

    // Wall colliders
    PlanCollider groundCollider = PlanCollider(Vec2(0.0,0.0), Vec2(0.0,1.0));
    PlanCollider leftWall = PlanCollider(Vec2(0,0), Vec2(1,0));
    PlanCollider rightWall = PlanCollider(Vec2(15,0), Vec2(-1, 0));

    this->colliders.push_back(groundCollider);
    this->colliders.push_back(leftWall);
    this->colliders.push_back(rightWall);

    // Rectangular box
    BoxCollider box = BoxCollider(Vec2(7,3), Vec2(0,1), 2, 7);
    this->colliders.push_back(box);

    // Static sphere

    SphereCollider sphereCollider = SphereCollider(Vec2(2,3), 1.0, true);
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

std::vector<std::variant<PlanCollider,SphereCollider, BoxCollider>>& Context::getColliders() {
    return colliders;
}

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
    applyFriction(dt);
    updateExpectedPosition(dt);

    addStaticContactConstraints();
    addDynamicContactConstraints(dt);
    projectConstraints();
    deleteContactConstraints();


    destroyParticles();     // Destructions of the particles after too many dynamic collisions

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

    for(int i=0; i<colliders.size(); i++) {
        for(int j=0; j<particles.size(); j++) {

            // variants and visitors as an alternative to inheritance
            using colliderVariant = std::variant<PlanCollider, SphereCollider, BoxCollider>;
            colliderVariant coll_var = colliders[i];
            auto sc = std::visit([j, this](auto arg)->std::optional<StaticConstraint>{return arg.checkContact(this->particles[j]);}, coll_var);

            if (sc.has_value()){
                StaticConstraint sc_val = sc.value();
                staticConstraints.push_back(sc_val);
                if(std::visit([](auto arg)->bool{return arg.canDestroy();}, coll_var)) {
                    particles[j].addCollision();
                }
            }
        }
    }
}

void Context::addDynamicContactConstraints(float dt) {
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
    std::vector<StaticConstraint>& staticConstraints = getStaticConstraints();
    for (int i=0; i<staticConstraints.size(); i++){
        Particle* part = staticConstraints[i].part_ptr;
        part->setExpPos(part->getExpPos()+solve(staticConstraints[i]));
    }
  
    // Dynamic constraints
    for(int i=0; i<dynamicConstraints.size(); i++) {
        dynamicConstraints[i].enforceDynamicConstraint();
    }
}

void Context::applyFriction(float dt) {
    // fluid friction
    float Cx = 0.5; // constant for a sphere
    float rho = 1.3;

    for (int i=0; i<particles.size(); i++){
        Vec2 v = particles[i].getVelocity();
        float r = particles[i].getRad();
        float S = M_PI * r * r;

        Vec2 F = -(1.0/2.0)*Cx*rho*S*v.length()*v;
        particles[i].setVelocity(v + F * (dt/particles[i].getMass()));
    }
}

void Context::deleteContactConstraints() {
    staticConstraints.clear();
    dynamicConstraints.clear();
}

// Destroys the particles after too many collisions
void Context::destroyParticles() {
    particles.erase(std::remove_if(particles.begin(),particles.end(), [](Particle part) { return part.checkNbCollisions(); }), particles.end());
}

// Reset the context (remove all particles)
void Context::reset() {
    particles.clear();
}
