#include "plancollider.h"
#include "vec2.h"
PlanCollider::PlanCollider(Vec2 pc_, Vec2 nc_)
    : Collider(), pc(pc_), nc((1.0/nc_.length())*nc_), isKiller(false) {
}

PlanCollider::PlanCollider(Vec2 pc_, Vec2 nc_, bool isKiller_)
    : Collider(), pc(pc_), nc((1.0/nc_.length())*nc_), isKiller(isKiller_) {
}

std::optional<StaticConstraint> PlanCollider::checkContact(Particle& collider) {
    Vec2 expPos = collider.getExpPos();
    Vec2 diff = expPos - getCenter();
    float ri = collider.getRad();

    if(diff.dotProduct(getNormal()) - ri < 0.0) {
        StaticConstraint sc;
        sc.pc = getCenter();
        sc.nc = getNormal();
        sc.part_ptr = &collider;
        return sc;
    }
    return {};
}

Vec2 PlanCollider::getCenter() {
    return pc;
}

Vec2 PlanCollider::getNormal() {
    return nc;
}

bool PlanCollider::canDestroy() {
    return isKiller;
}
