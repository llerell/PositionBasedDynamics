#include "context.h"


Context::Context() {
    this->collisions = false;
    this->particles = std::vector<Particle>();
    this->colliders = std::vector<std::variant<PlaneCollider,SphereCollider, BoxCollider>>();
    this->staticConstraints = std::vector<StaticConstraint>();
    this->dynamicConstraints = std::vector<DynamicConstraint>();

    // Wall colliders
    const PlaneCollider groundCollider = PlaneCollider(Vec2(0.0,0.0), Vec2(0.0,1.0));
    const PlaneCollider leftWall = PlaneCollider(Vec2(0,0), Vec2(1,0));
    const PlaneCollider rightWall = PlaneCollider(Vec2(15,0), Vec2(-1, 0));

    this->colliders.push_back(groundCollider);
    this->colliders.push_back(leftWall);
    this->colliders.push_back(rightWall);

    // Rectangular box
    const BoxCollider box = BoxCollider(Vec2(7,3), Vec2(0,1), 2, 7);
    this->colliders.push_back(box);

    // Static sphere
    const SphereCollider sphereCollider = SphereCollider(Vec2(2,3), 1.0, 1);
    this->colliders.push_back(sphereCollider);

    const SphereCollider healCollider = SphereCollider(Vec2(5,5), 1.0, 2);
    this->colliders.push_back(healCollider);
}


void Context::addParticle(const Particle particle) {
    this->particles.push_back(particle);
}

const int Context::getNbParticles() const {
    return particles.size();
}

const std::vector<Particle>& Context::getParticles() const {
    return particles;
}

const std::vector<std::variant<PlaneCollider, SphereCollider, BoxCollider>> Context::getColliders() const {
    return colliders;
}

const bool Context::getCollisionsToggle() const {
    return collisions;
}

void Context::updatePhysicalSystem(const float dt) {
    applyExternalForce(dt);
    applyFriction(dt);
    updateExpectedPosition(dt);

    addStaticContactConstraints();
    addDynamicContactConstraints();
    projectConstraints();
    deleteContactConstraints();

    destroyParticles();
    updateVelocityAndPosition(dt);
}


void Context::destroyParticles() {
    // In the vector particles, removes every particle that satisfies the condition
    particles.erase(std::remove_if(particles.begin(),particles.end(), [](Particle part) { return part.checkNbCollisions(); }), particles.end());
}

void Context::reset() {
    particles.clear();
}

void Context::changeCollisions() {
    collisions = !(collisions);
}


void Context::applyExternalForce(const float dt) {

    // Gravity
    float m;
    float g = 9.81;

    for(int i=0; i<particles.size(); i++) {
        m = particles[i].getMass();
        const Vec2 Fg = Vec2(0,-m*g);

        particles[i].setVelocity(particles[i].getVelocity() + Fg * (dt/m));
    }

}

void Context::updateExpectedPosition(const float dt) {
    for(int i=0; i<particles.size(); i++) {
        particles[i].setExpPos(particles[i].getPos() + particles[i].getVelocity() * dt);
    }
}

void Context::updateVelocityAndPosition(const float dt) {
    for(int i=0; i<particles.size(); i++) {
        particles[i].setVelocity((particles[i].getExpPos() - particles[i].getPos())*(1/dt));
        particles[i].setPos(particles[i].getExpPos());
    }
}


void Context::addStaticContactConstraints() {

    for(int i=0; i<colliders.size(); i++) {
        for(int j=0; j<particles.size(); j++) {

            // variants and visitors as an alternative to inheritance
            using colliderVariant = std::variant<PlaneCollider, SphereCollider, BoxCollider>;
            const colliderVariant coll_var = colliders[i];
            const auto sc = std::visit([j, this](auto arg)->std::optional<StaticConstraint>{return arg.checkContact(this->particles[j]);}, coll_var);

            if (sc.has_value()){
                const StaticConstraint sc_val = sc.value();
                staticConstraints.push_back(sc_val);
                if(collisions) {
                    const int role = std::visit([](auto arg)->int{return arg.getRole();}, coll_var);
                    switch(role) {
                    case 1:
                        particles[j].addCollision();
                        break;
                    case 2:
                        particles[j].removeCollision();
                        break;
                    }
                }
            }
        }
    }
}

void Context::addDynamicContactConstraints() {
    for(int i=0; i<particles.size(); i++) {
        for(int j=i+1; j<particles.size(); j++) {
            const std::optional<DynamicConstraint> dc = checkDynamicContact(particles[i], particles[j]);
            if(dc.has_value()) {
                dynamicConstraints.push_back(dc.value());

                if(collisions) {
                // Increases counter of contacts
                    particles[i].addCollision();
                    particles[j].addCollision();
                }
            }
        }
    }
}

const std::optional<DynamicConstraint> Context::checkDynamicContact(Particle& part1, Particle& part2) {
    const Vec2 p1 = part1.getExpPos();
    const Vec2 p2 = part2.getExpPos();
    const float r1 = part1.getRad();
    const float r2 = part2.getRad();
    const float d = (p1-p2).length();
    if((r1+r2)-d>0) {
        return DynamicConstraint {&part1, &part2};
    }
    else {
        return {};
    }
}

void Context::projectConstraints() {

    // Static constraints
    for (int i=0; i<staticConstraints.size(); i++){
        staticConstraints[i].enforceStaticConstraint();
    }
  
    // Dynamic constraints
    for(int i=0; i<dynamicConstraints.size(); i++) {
        dynamicConstraints[i].enforceDynamicConstraint();
    }
}


void Context::applyFriction(const float dt) {
    // fluid friction
    const float Cx = 0.5; // constant for a sphere
    const float rho = 1.3;

    for (int i=0; i<particles.size(); i++){
        const Vec2 v = particles[i].getVelocity();
        const float r = particles[i].getRad();
        const float S = M_PI * r * r; // contact surface for a sphere = disc

        const Vec2 F = -(1.0/2.0)*Cx*rho*S*v.length()*v;

        particles[i].setVelocity(v + F * (dt/particles[i].getMass()));
    }
}

void Context::deleteContactConstraints() {
    staticConstraints.clear();
    dynamicConstraints.clear();
}
