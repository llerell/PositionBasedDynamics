#include "spherecollider.h"

SphereCollider::SphereCollider(Vec2 pc_, float rc_)
    : Collider(), pc(pc_), rc(rc_) {}

std::optional<StaticConstraint> SphereCollider::checkContact(const Particle& collider) {
    std::optional<StaticConstraint> sc;
    return sc;
}

Vec2 SphereCollider::getCenter() {
    return pc;
}

float SphereCollider::getRadius() {
    return rc;
}
