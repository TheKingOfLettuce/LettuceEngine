#pragma once
#include "LettuceEngine/Utils/json.hpp"

namespace LettuceEngine { namespace Math {
    class Color {
        public:
            Color();
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

            unsigned char R;
            unsigned char G;
            unsigned char B;
            unsigned char A;

            Color operator- (const Color& c) const;
            Color operator+ (const Color& c) const;
            Color operator/ (const Color& c) const;
            Color operator* (const Color& c) const;
            void operator+= (const Color& c);
            void operator-= (const Color& c);
            void operator*= (const Color& c);
            void operator/= (const Color& c);
            bool operator== (const Color& c) const;
            bool operator!= (const Color& c) const;
            void operator= (const Color& c);
    };

    void to_json(nlohmann::json& j, const Color& c);
    void from_json(const nlohmann::json& j, Color& c);
}}