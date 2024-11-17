#pragma once

#include "Raylib/raylib.h"
#include "LettuceEngine/Math/Vector2.h"

class RaylibDrawing {
    public:
        static void DrawTexture(const LettuceEngine::Math::Vector2& point, Texture2D texture, const ::Color& color, const LettuceEngine::Math::Vector2& scale, const float rotation = 0);
};