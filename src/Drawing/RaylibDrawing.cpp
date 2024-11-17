#include "LettuceEngine/Drawing/RaylibDrawing.h"

using LVector2 = LettuceEngine::Math::Vector2;

void RaylibDrawing::DrawTexture(const LVector2& point, Texture2D texture, const ::Color& color, const LVector2& scale, const float rotation) {
    // TODO add custom pivot to texture thats not just center
    ::DrawTexturePro(texture, ::Rectangle({0, 0, (float)texture.width, (float)texture.height}), 
        ::Rectangle({point.X, point.Y, texture.width*scale.X, texture.height*scale.Y}), ::Vector2({(texture.width >> 1)*scale.X, (texture.height >> 1)*scale.Y}), rotation, color);
}