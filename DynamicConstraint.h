#ifndef DYNAMICCONSTRAINT_H
#define DYNAMICCONSTRAINT_H

#include "particle.h"
struct DynamicConstraint {
    Particle* ptr_part1;
    Particle* ptr_part2;
    ~DynamicConstraint() {}

    void enforceDynamicConstraint();
};

inline void DynamicConstraint::enforceDynamicConstraint() {
    Vec2 p1 = ptr_part1->getExpPos();
    Vec2 p2 = ptr_part2->getExpPos();
    float r1 = ptr_part1->getRad();
    float r2 = ptr_part2->getRad();
    float m1 = ptr_part1->getMass();
    float m2 = ptr_part2->getMass();
    float d = (p1-p2).length();
    float C = d - (r1+r2);
    float sig1 = ((1.0/m1)/((1.0/m1)+(1.0/m2)))*C;
    float sig2 = ((1.0/m2)/((1.0/m1)+(1.0/m2)))*C;
    Vec2 delta1 = (-sig1/d)*(p1-p2);
    Vec2 delta2 = (sig2/d)*(p1-p2);
    ptr_part1->setExpPos(p1+delta1);
    ptr_part2->setExpPos(p2+delta2);
}

#endif // DYNAMICCONSTRAINT_H
