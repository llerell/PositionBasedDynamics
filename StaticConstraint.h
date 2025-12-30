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
};



#endif // STATICCONSTRAINT_H
