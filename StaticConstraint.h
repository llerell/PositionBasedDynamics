#ifndef STATICCONSTRAINT_H
#define STATICCONSTRAINT_H

#include "vec2.h"
#include "particle.h"

// Constraint of type
struct StaticConstraint
{
    // Maybe also the particle and the collider that are in contact too
    Vec2 pc;
    Vec2 nc;
    Particle* part_ptr;
};



#endif // STATICCONSTRAINT_H
