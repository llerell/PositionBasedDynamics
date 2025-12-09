#ifndef VEC2_H
#define VEC2_H
#include <cmath>
#include <iostream>


class Vec2 {
public:
    Vec2(float x_, float y_);

    Vec2 operator+(const Vec2& v);

    Vec2 operator-(const Vec2& v);

    Vec2 operator*(const float scal);

    std::ostream& operator<<(std::ostream& out);

    float dotProduct(const Vec2& v);

    float squaredLength();

    float length();

    float& getX();

    float& getY();


private:
    float x;
    float y;
};


#endif // VEC2_H
