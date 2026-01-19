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
    BoxCollider(const Vec2 pc_, const Vec2 u_, const float width_, const float height_);

    BoxCollider(const Vec2 pc_, const Vec2 u_, const float width_, const float height_, const bool isKiller_, const bool isHealer_);

    /// Destructor for BoxCollider class.
    ~BoxCollider() override = default;

    /**
     * @brief check if collider particle is in contact with the rectangular collider.
     * @param collider Particle to check
     * @return StaticConstraint corresponding to the box and the particle if in contact.
     */
    std::optional<StaticConstraint> checkContact(Particle &collider) override;

    const Vec2 getPoint() const override;

    const Vec2 getU() const;

    const Vec2 getV() const;

    const float getWidth() const;

    const float getHeight() const;

private:
    Vec2 u, v, pc;

    float width, height;

    bool isKiller;
};

#endif // BOXCOLLIDER_H
