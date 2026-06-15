#include "planecollider.h"
#include "vec2.h"


PlaneCollider::PlaneCollider(const Vec2 pc_, const Vec2 nc_)
    : Collider(), pc(pc_), nc((1.0/nc_.length())*nc_) {
}


PlaneCollider::PlaneCollider(const Vec2 pc_, const Vec2 nc_, const int role_)
    : Collider(role_), pc(pc_), nc((1.0/nc_.length())*nc_) {}

const std::optional<StaticConstraint> PlaneCollider::checkContact(Particle& collider) {
    const Vec2 expPos = collider.getExpPos();
    const Vec2 diff = expPos - getPoint();
    const float ri = collider.getRad();

    if(diff.dotProduct(getNormal()) - ri < 0.0) {
        StaticConstraint sc;
        sc.pc = getPoint();
        sc.nc = getNormal();
        sc.part_ptr = &collider;
        return sc;
    }
    return {};
}


const Vec2 PlaneCollider::getPoint() const {
    return pc;
}

const Vec2 PlaneCollider::getNormal() const {
    return nc;
}

