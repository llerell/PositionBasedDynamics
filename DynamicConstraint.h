#ifndef DYNAMICCONSTRAINT_H
#define DYNAMICCONSTRAINT_H

#include "particle.h"

struct DynamicConstraint {
    std::shared_ptr<Particle> ptr_part1;
    std::shared_ptr<Particle> ptr_part2;
    ~DynamicConstraint() {}

    void enforceDynamicConstraint();
};

inline void DynamicConstraint::enforceDynamicConstraint() {
    const Vec2 p1 = ptr_part1->getExpPos();
    const Vec2 p2 = ptr_part2->getExpPos();
    const float r1 = ptr_part1->getRad();
    const float r2 = ptr_part2->getRad();
    const float m1 = ptr_part1->getMass();
    const float m2 = ptr_part2->getMass();
    const float d = (p1-p2).length();
    const float C = d - (r1+r2);

    const float sig1 = ((1.0/m1)/((1.0/m1)+(1.0/m2)))*C;
    const float sig2 = ((1.0/m2)/((1.0/m1)+(1.0/m2)))*C;

    const Vec2 delta1 = (-sig1/d)*(p1-p2);
    const Vec2 delta2 = (sig2/d)*(p1-p2);

    ptr_part1->setExpPos(p1+delta1);
    ptr_part2->setExpPos(p2+delta2);
}

#endif // DYNAMICCONSTRAINT_H
