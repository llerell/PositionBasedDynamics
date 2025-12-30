#include "spherecollider.h"

SphereCollider::SphereCollider(Vec2 pc_, float rc_)
    : Collider(), pc(pc_), rc(rc_) {}

std::optional<StaticConstraint> SphereCollider::checkContact(const Particle& collider) {
    Vec2 diff = collider.getExpPos()-this->getCenter();
    float sdf = diff.length() - collider.getRad();
    if (sdf<0){
        StaticConstraint sc;
        sc.nc = (1/diff.length())*diff;
        sc.pc = collider.getExpPos()-sdf * sc.nc;
        sc.part_ptr = &collider;
        return sc;
    }
    return {};
}

Vec2 SphereCollider::getCenter() {
    return pc;
}

float SphereCollider::getRadius() {
    return rc;
}
