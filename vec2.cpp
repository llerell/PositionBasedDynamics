#include "vec2.h"

Vec2::Vec2(float x_, float y_)
    : x(x_), y(y_) {}

Vec2 Vec2::operator+(const Vec2& v) {
    return Vec2(this->x + v.x, this->y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) {
    return Vec2(this->x - v.x, this->y - v.y);
}

Vec2 Vec2::operator*(const float scal) {
    return Vec2(scal*this->x, scal*this->y);
}

Vec2 operator*(const float scal, Vec2 const& v) {
    const Vec2 u = Vec2(scal*v.x, scal*v.y);
    return u;
}

std::ostream& operator<<(std::ostream& out, Vec2 const& v) {
    return out << v.x << ", " << v.y;
}

float Vec2::dotProduct(const Vec2& v) {
    return this->x * v.x + this->y * v.y;
}

float Vec2::squaredLength() {
    return this->x * this->x + this->y * this->y;
}

float Vec2::length() {
    return sqrt(this->squaredLength());
}

float& Vec2::getX() {
    return x;
}

float& Vec2::getY() {
    return y;
}

