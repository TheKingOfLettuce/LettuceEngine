#include "LettuceEngine/Math/Color.h"

using json = nlohmann::json;
using LettuceEngine::Math::Color;

Color::Color() {
    R = 255;
    G = 255;
    B = 255;
    A = 255;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    R = r;
    G = g;
    B = b;
    A = a;
}

Color Color::operator+(const Color& c) const {
    Color toReturn;
    short temp = this->R + c.R;
    toReturn.R = temp > 255 ? 255 : temp;
    temp = this->G + c.G;
    toReturn.G = temp > 255 ? 255 : temp;
    temp = this->B + c.B;
    toReturn.B = temp > 255 ? 255 : temp;
    temp = this->A + c.A;
    toReturn.A = temp > 255 ? 255 : temp;
    
    return toReturn;
}

Color Color::operator-(const Color& c) const {
    Color toReturn;
    short temp = this->R - c.R;
    toReturn.R = temp < 0 ? 0 : temp;
    temp = this->G - c.G;
    toReturn.G = temp < 0 ? 0 : temp;
    temp = this->B - c.B;
    toReturn.B = temp < 0 ? 0 : temp;
    temp = this->A - c.A;
    toReturn.A = temp < 0 ? 0 : temp;
    
    return toReturn;
}

Color Color::operator*(const Color& c) const {
    Color toReturn;
    unsigned short temp = this->R * c.R;
    toReturn.R = temp > 255 ? 255 : temp;
    temp = this->G * c.G;
    toReturn.G = temp > 255 ? 255 : temp;
    temp = this->B * c.B;
    toReturn.B = temp > 255 ? 255 : temp;
    temp = this->A * c.A;
    toReturn.A = temp > 255 ? 255 : temp;
    
    return toReturn;
}

Color Color::operator/(const Color& c) const {
    Color toReturn;
    unsigned short temp = c.R != 0 ? this->R / c.R : 0;
    toReturn.R = temp < 0 ? 0 : temp;
    temp = c.G != 0 ? this->G / c.G : 0;
    toReturn.G = temp < 0 ? 0 : temp;
    temp = c.B != 0 ? this->B / c.B : 0;
    toReturn.B = temp < 0 ? 0 : temp;
    temp = c.A != 0 ? this->A / c.A : 0;
    toReturn.A = temp < 0 ? 0 : temp;
    
    return toReturn;
}

void Color::operator+=(const Color& c) {
    short temp = this->R + c.R;
    this->R = temp > 255 ? 255 : temp;
    temp = this->G + c.G;
    this->G = temp > 255 ? 255 : temp;
    temp = this->B + c.B;
    this->B = temp > 255 ? 255 : temp;
    temp = this->A + c.A;
    this->A = temp > 255 ? 255 : temp;
}

void Color::operator-=(const Color& c) {
    short temp = this->R - c.R;
    this->R = temp < 0 ? 0 : temp;
    temp = this->G - c.G;
    this->G = temp < 0 ? 0 : temp;
    temp = this->B - c.B;
    this->B = temp < 0 ? 0 : temp;
    temp = this->A - c.A;
    this->A = temp < 0 ? 0 : temp;
}

void Color::operator*=(const Color& c) {
    unsigned short temp = this->R * c.R;
    this->R = temp > 255 ? 255 : temp;
    temp = this->G * c.G;
    this->G = temp > 255 ? 255 : temp;
    temp = this->B * c.B;
    this->B = temp > 255 ? 255 : temp;
    temp = this->A * c.A;
    this->A = temp > 255 ? 255 : temp;
}

void Color::operator/=(const Color& c) {
    unsigned short temp = c.R != 0 ? this->R / c.R : 0;
    this->R = temp < 0 ? 0 : temp;
    temp = c.G != 0 ? this->G / c.G : 0;
    this->G = temp < 0 ? 0 : temp;
    temp = c.B != 0 ? this->B / c.B : 0;
    this->B = temp < 0 ? 0 : temp;
    temp = c.A != 0 ? this->A / c.A : 0;
    this->A = temp < 0 ? 0 : temp;
}

bool Color::operator==(const Color& c) const {
    return (this->R == c.R) && (this->G == c.G) 
        && (this->B == c.B) && (this->A == c.A); 
}

bool Color::operator!= (const Color& c) const {
    return ! operator==(c);
}

void Color::operator= (const Color& c) {
    this->R = c.R;
    this->G = c.G;
    this->B = c.B;
    this->A = c.A;
}

void LettuceEngine::Math::to_json(json& j, const Color& c) {
    j = json {
        {"r", c.R},
        {"g", c.G},
        {"b", c.B},
        {"a", c.A}
    };
}

void LettuceEngine::Math::from_json(const json& j, Color& c) {
    j.at("r").get_to(c.R);
    j.at("g").get_to(c.G);
    j.at("b").get_to(c.B);
    j.at("a").get_to(c.A);
}
