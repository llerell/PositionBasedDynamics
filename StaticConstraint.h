#ifndef STATICCONSTRAINT_H
#define STATICCONSTRAINT_H

#include "vec2.h"
#include "particle.h"

// linearised constraint of type (pi-pc)^T.nc - ri < 0
struct StaticConstraint
{
    Vec2 pc;
    Vec2 nc;
    Particle* part_ptr;

    /**
     * @brief solve constraint and adjust expected position of the particle accordingly.
     */
    void enforceStaticConstraint();
};

inline void StaticConstraint::enforceStaticConstraint()
{
    const Vec2 p = this->part_ptr->getExpPos();
    const Vec2 qc = p - (((p - this->pc).dotProduct(this->nc))*this->nc);
    const Vec2 diff = p - qc;
    const float C = diff.dotProduct(this->nc) - this->part_ptr->getRad();
    const Vec2 delta = - C * this->nc;
    part_ptr->setExpPos(p+delta);
}

#endif // STATICCONSTRAINT_H
