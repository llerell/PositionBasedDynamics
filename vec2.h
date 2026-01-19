#ifndef VEC2_H
#define VEC2_H
#include <cmath>
#include <iostream>

/**
 * @brief The Vec2 class implements 2-dimensional vectors with float coordinates.
 */
class Vec2 {
public:
    Vec2(float x_, float y_);
    Vec2();

    const Vec2 operator+(const Vec2& v) const;

    const Vec2 operator-(const Vec2& v) const;

    const Vec2 operator*(const float scal) const;

    friend const Vec2 operator*(const float scal, Vec2 const& v);

    friend std::ostream& operator<<(std::ostream& out, Vec2 const& v);

    const float dotProduct(const Vec2& v) const;

    const float squaredLength() const;

    const float length() const;

    const float& getX() const;

    const float& getY() const;


private:
    float x;
    float y;
};


#endif // VEC2_H
