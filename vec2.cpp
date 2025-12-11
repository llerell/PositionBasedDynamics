#include "vec2.h"

Vec2::Vec2(float x_, float y_)
    : x(x_), y(y_) {}

Vec2 Vec2::operator+(const Vec2& v) {
    const Vec2 u = Vec2(this->x + v.x, this->y + v.y);
    return u;
}

Vec2 Vec2::operator-(const Vec2& v) {
    const Vec2 u = Vec2(this->x - v.x, this->y - v.y);
    return u;
}

Vec2 Vec2::operator*(const float scal) {
    const Vec2 u = Vec2(scal*this->x, scal*this->y);
    return u;
}

Vec2 operator*(const float scal, Vec2 const& v) {
    const Vec2 u = Vec2(scal*v.x, scal*v.y);
    return u;
}

std::ostream& Vec2::operator<<(std::ostream& out) {
    return out << this->x << ", " << this->y;
}

float Vec2::dotProduct(const Vec2& v) {
    const float res = this->x * v.x + this->y * v.y;
    return res;
}

float Vec2::squaredLength() {
    float res = this->x * this->x + this->y * this->y;
    return res;
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
