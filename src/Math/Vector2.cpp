#include "LettuceEngine/Math/Vector2.h"

using json = nlohmann::json;
using LettuceEngine::Math::Vector2;

Vector2::Vector2() {
    X = 0;
    Y = 0;
}

Vector2::Vector2(float x, float y) {
    X = x;
    Y = y;
}

float Vector2::Magnitude() {
    return sqrtf((X*X) + (Y * Y));
}

void Vector2::Normalize() {
    float length = Magnitude();
    if (length == 0) {
        *this = ZERO;
        return;
    }
    *this /= length;
}

Vector2 Vector2::operator+(const Vector2 v) const {
    Vector2 toReturn = Vector2();
    toReturn.X = this->X + v.X;
    toReturn.Y = this->Y + v.Y;

    return toReturn;
}

Vector2 Vector2::operator-(const Vector2 v) const {
    Vector2 toReturn = Vector2();
    toReturn.X = this->X - v.X;
    toReturn.Y = this->Y - v.Y;

    return toReturn;
}

Vector2 Vector2::operator*(const Vector2 v) const {
    Vector2 toReturn = Vector2();
    toReturn.X = this->X * v.X;
    toReturn.Y = this->Y * v.Y;

    return toReturn;
}

Vector2 Vector2::operator/(const Vector2 v) const {
    Vector2 toReturn = Vector2();
    toReturn.X = this->X / v.X;
    toReturn.Y = this->Y / v.Y;

    return toReturn;
}

void Vector2::operator+=(const Vector2 v) {
    this->X += v.X;
    this->Y += v.Y;
}

void Vector2::operator-=(const Vector2 v) {
    this->X -= v.X;
    this->Y -= v.Y;
}

void Vector2::operator*=(const Vector2 v) {
    this->X *= v.X;
    this->Y *= v.Y;
}

void Vector2::operator/=(const Vector2 v) {
    this->X /= v.X;
    this->Y /= v.Y;
}

bool Vector2::operator==(const Vector2 v) const {
    return (this->X == v.X) && (this->Y == v.Y);
}

bool Vector2::operator!=(const Vector2 v) const {
    return !operator==(v);
}

void Vector2::operator=(const Vector2 v) {
    this->X = v.X;
    this->Y = v.Y;
}

Vector2 Vector2::operator*(const float scale) {
    Vector2 toReturn;
    toReturn.X = this->X * scale;
    toReturn.Y = this->Y * scale;

    return toReturn;
}

void Vector2::operator*=(const float scale) {
    this->X *= scale;
    this->Y *= scale;
}

Vector2 Vector2::operator/(const float scale) {
    Vector2 toReturn;
    toReturn.X = this->X / scale;
    toReturn.Y = this->Y / scale;

    return toReturn;
}

void Vector2::operator/=(const float scale) {
    this->X /= scale;
    this->Y /= scale;
}

const Vector2 Vector2::ZERO = Vector2(0, 0);
const Vector2 Vector2::ONE = Vector2(1, 1);

std::string Vector2::ToString() const {
    return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
}

void LettuceEngine::Math::to_json(json& j, const Vector2& v) {
    j = json {
        {"x", v.X},
        {"y", v.Y}
    };
}

void LettuceEngine::Math::from_json(const json& j, Vector2& v) {
    j.at("x").get_to(v.X);
    j.at("y").get_to(v.Y);
}

std::ostream& LettuceEngine::Math::operator<<(std::ostream& os, const Vector2& vector ) {
    os << vector.ToString();
    return os;
}