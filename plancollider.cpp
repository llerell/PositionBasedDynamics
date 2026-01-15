#include "plancollider.h"
#include "vec2.h"
PlanCollider::PlanCollider(Vec2 pc_, Vec2 nc_)
    : Collider(), pc(pc_), nc((1.0/nc_.length())*nc_) {
}

PlanCollider::PlanCollider(Vec2 pc_, Vec2 nc_, bool isKiller_, bool isHealer_)
    : Collider(isKiller_, isHealer_), pc(pc_), nc((1.0/nc_.length())*nc_) {}

std::optional<StaticConstraint> PlanCollider::checkContact(Particle& collider) {
    Vec2 expPos = collider.getExpPos();
    Vec2 diff = expPos - getPoint();
    float ri = collider.getRad();

    if(diff.dotProduct(getNormal()) - ri < 0.0) {
        StaticConstraint sc;
        sc.pc = getPoint();
        sc.nc = getNormal();
        sc.part_ptr = &collider;
        return sc;
    }
    return {};
}

Vec2 PlanCollider::getPoint() {
    return pc;
}

Vec2 PlanCollider::getNormal() {
    return nc;
}
