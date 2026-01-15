#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "collider.h"
#include "vec2.h"

class BoxCollider : public Collider
{
public:
    BoxCollider(Vec2 pc_, Vec2 u_, float width_, float height_);

    BoxCollider(Vec2 pc_, Vec2 u_, float width_, float height_, bool ilKiller_, bool isHealer_);

    ~BoxCollider() override {}

    std::optional<StaticConstraint> checkContact(Particle& collider) override;

    Vec2 getPoint() override;
    Vec2 getU();
    Vec2 getV();
    float getWidth();
    float getHeight();

private:
    Vec2 u, v, pc;
    float width, height;
};

#endif // BOXCOLLIDER_H
