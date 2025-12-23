#include "plancollider.h"

PlanCollider::PlanCollider(Vec2 pc_, Vec2 nc_)
    : Collider(), pc(pc_), nc(nc_) {}


std::optional<StaticConstraint> PlanCollider::checkContact(const Particle& collider) {
    std::optional<StaticConstraint> sc;
    Vec2 expPos = collider.getExpPos();
    Vec2 diff = expPos - this->pc;
    float ri = collider.getRad();
    if(diff.dotProduct(this->nc) - ri <0) {
        sc = StaticConstraint({diff.dotProduct(this->nc),ri});
    }
    return sc;
}

Vec2 PlanCollider::getCenter() {
    return pc;
}

Vec2 PlanCollider::getNormal() {
    return nc;
}
