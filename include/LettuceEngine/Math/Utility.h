#pragma once
#include <cmath>

namespace LettuceEngine { namespace Math {
    const double PI = std::atan(1.0)*4;
    const float PI_F = std::atan(1.0f)*4;
    class Utility {
        inline static float DegreeToRadian(float degrees) {
            return degrees * PI_F / 180;
        }

        inline static double DegreeToRadian(double degrees) {
            return degrees * PI / 180;
        }

        inline static float RadianToDegree(float radians) {
            return radians * 180 / PI_F;
        }

        inline static double RadianToDegree(double radians) {
            return radians * 180 / PI;
        }
    };
}}