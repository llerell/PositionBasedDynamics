#include "spherecollider.h"

SphereCollider::SphereCollider(Vec2 pc_, float rc_)
    : Collider(), pc(pc_), rc(rc_) {

}

SphereCollider::SphereCollider(Vec2 pc_, float rc_, bool isKiller_, bool isHealer_)
    : Collider(isKiller_, isHealer_), pc(pc_), rc(rc_) {}

std::optional<StaticConstraint> SphereCollider::checkContact(Particle& collider) {
    Vec2 diff = collider.getExpPos()-this->getPoint();
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

Vec2 SphereCollider::getPoint() {
    return pc;
}

float SphereCollider::getRadius() {
    return rc;
}

//bool SphereCollider::canDestroy() {
//    return isKiller;
//}
