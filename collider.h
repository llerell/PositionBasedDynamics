#ifndef COLLIDER_H
#define COLLIDER_H

#include "StaticConstraint.h"
#include "particle.h"
#include <optional>


// Abstract class that defines collider objects
class Collider
{
public:
    /**
     * @brief Collider
     * default role is 0 (neutral collider)
     * default color is black
     */
    Collider();

    /**
     * @brief Collider
     * color is defined based on the role
     * @param role_ whether the collider can destroy or heal the particles
     */
    Collider(const int role_);

    /// Destructor for Collider class.
    virtual ~Collider() {}

    /**
     * @brief check if collider is in contact with the collider.
     * If so, returns the corresponding StaticConstraint.
     * @param collider Particle to check
     * @return StaticConstraint corresponding to the collider and the particle if in contact.
     */
    virtual const std::optional<StaticConstraint> checkContact(Particle& collider) =0;

    virtual const Vec2 getPoint() const = 0;

    const int getRole() const;

    const QColor getColor() const;

protected:
    /// Role of the collider
    /// 0 if the collider does nothing, 1 if it can destroy the particles, 2 if it can heal them
    const int role;
    QColor color;
};

#endif // COLLIDER_H
