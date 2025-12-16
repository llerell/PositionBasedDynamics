#include "vec2.h"

Vec2::Vec2(float x_, float y_)
    : x(x_), y(y_) {}

const Vec2 Vec2::operator +(const Vec2& v) const {
    return Vec2(this->x + v.x, this->y + v.y);
}

const Vec2 Vec2::operator -(const Vec2& v) const {
    return Vec2(this->x - v.x, this->y - v.y);
}

const Vec2 Vec2::operator *(const float scal) const {
    return Vec2(scal*this->x, scal*this->y);
}

const Vec2 operator*(const float scal, Vec2 const& v) {
    const Vec2 u = Vec2(scal*v.x, scal*v.y);
    return u;
}

const std::ostream& operator<<(std::ostream& out, Vec2 const& v) {
    return out << v.x << ", " << v.y;
}

const float Vec2::dotProduct(const Vec2& v) const {
    return this->x * v.x + this->y * v.y;
}

const float Vec2::squaredLength() const {
    return this->x * this->x + this->y * this->y;
}

const float Vec2::length() const {
    return sqrt(this->squaredLength());
}

const float &Vec2::getX() const {
    return x;
}

const float &Vec2::getY() const {
    return y;
}

