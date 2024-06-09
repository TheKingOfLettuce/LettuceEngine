#pragma once
#include "LettuceEngine/Utils/json.hpp"
#include <string>

namespace LettuceEngine { namespace Math {

class Vector2 {
    public:
        float X;
        float Y;

        Vector2();
        Vector2(float x, float y);

        float Magnitude();
        void Normalize();

        Vector2 operator+(const Vector2 v) const;
        Vector2 operator-(const Vector2 v) const;
        Vector2 operator*(const Vector2 v) const;
        Vector2 operator/(const Vector2 v) const;
        void operator+=(const Vector2 v);
        void operator-=(const Vector2 v);
        void operator*=(const Vector2 v);
        void operator/=(const Vector2 v);
        bool operator==(const Vector2 v) const;
        bool operator!=(const Vector2 v) const;
        void operator=(const Vector2 v);

        Vector2 operator*(const float scale);
        void operator*=(const float scale);
        Vector2 operator/(const float scale);
        void operator/=(const float scale);

        std::string ToString() const;

        static Vector2 Zero();
};

void to_json(nlohmann::json& j, const Vector2& v);
void from_json(const nlohmann::json& j, Vector2& v);
std::ostream& operator<<(std::ostream& os, const Vector2& vector );
}}