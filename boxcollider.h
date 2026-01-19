#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "collider.h"
#include "vec2.h"

/**
 * BoxCollider class
 * Rectangular collider represented by its center, characteristic 2D vector, width and height.
 *
 */
class BoxCollider : public Collider
{
public:
    /**
     * @brief BoxCollider Constructor for BoxCollider class
     * @param pc_ position of the center of the rectangle
     * @param u_ characteristic vector, normal to the height of the rectangle.
     * @param width_
     * @param height_
     */
    BoxCollider(Vec2 pc_, Vec2 u_, float width_, float height_);

    /// Destructor for BoxCollider class.
    ~BoxCollider() override = default;

    /**
     * @brief check if collider particle is in contact with the rectangular collider.
     * @param collider Particle to check
     * @return StaticConstraint corresponding to the box and the particle if in contact.
     */
    std::optional<StaticConstraint> checkContact(Particle& collider) override;

    Vec2 getPoint() override;

    Vec2 getU();

    Vec2 getV();

    float getWidth();

    float getHeight();

    bool canDestroy();

private:
    Vec2 u, v, pc;

    float width, height;

    bool isKiller;
};

#endif // BOXCOLLIDER_H
