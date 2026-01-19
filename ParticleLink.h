#ifndef PARTICLELINK_H
#define PARTICLELINK_H
#include "particle.h"

struct ParticleLink {
    Particle* ptr_part1;
    Particle* ptr_part2;
    ~ParticleLink() = default;

    /**
     * @brief solve link and adjust expected positions of both particles accordingly.
     */
    void enforceParticleLink(int nbUpdates);
};

inline void ParticleLink::enforceParticleLink(int nbUpdates) {
    std::cout<<"enforcing between " << ptr_part1 << " and " << ptr_part2 <<std::endl;
    Vec2 p1 = ptr_part1->getExpPos();
    Vec2 p2 = ptr_part2->getExpPos();
    float r1 = ptr_part1->getRad();
    float r2 = ptr_part2->getRad();
    float m1 = ptr_part1->getMass();
    float m2 = ptr_part2->getMass();
    float d = (p1-p2).length();
    float C = d - (r1+r2+0.1);
    float gamma = 0.75;
    float beta = 1 - pow(1-gamma, 1.0/float(nbUpdates));
    float sig1 = ((1.0/m1)/((1.0/m1)+(1.0/m2)))*C*beta;
    float sig2 = ((1.0/m2)/((1.0/m1)+(1.0/m2)))*C*beta;

    Vec2 delta1 = (-sig1/d)*(p1-p2);
    Vec2 delta2 = (sig2/d)*(p1-p2);

    ptr_part1->setExpPos(p1+delta1);
    ptr_part2->setExpPos(p2+delta2);
}
#endif // PARTICLELINK_H
