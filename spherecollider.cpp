#include "spherecollider.h"

SphereCollider::SphereCollider(Vec2 pc_, float rc_)
    : Collider(), pc(pc_), rc(rc_), isKiller(false) {

}

SphereCollider::SphereCollider(Vec2 pc_, float rc_, bool isKiller_)
    : Collider(), pc(pc_), rc(rc_), isKiller(isKiller_) {

}

std::optional<StaticConstraint> SphereCollider::checkContact(Particle& collider) {
    Vec2 diff = collider.getExpPos()-this->getCenter();
    float sdf = diff.length() - this->getRadius();
    if (sdf<collider.getRad()){
        StaticConstraint sc;
        sc.nc = (1.0/diff.length())*diff;
        sc.pc = collider.getExpPos() - sdf * sc.nc;
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

bool SphereCollider::canDestroy() {
    return isKiller;
}
