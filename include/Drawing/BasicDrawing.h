#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "CollisionSystem/AABB.h"
#include <string>
#include <unordered_map>

class BasicDrawing {
    public:
        // Drawing
        static void DrawPixel(const LettuceEngine::Math::Vector2& point, const LettuceEngine::Math::Color& color);
        static void DrawCircle(const LettuceEngine::Math::Vector2& center, const LettuceEngine::Math::Color& color, const float radius);
        static void DrawElipse(const LettuceEngine::Math::Vector2& center, const LettuceEngine::Math::Color& color, const LettuceEngine::Math::Vector2& radius);
        static void DrawRectangle(const LettuceEngine::Math::Vector2& center, const LettuceEngine::Math::Color& color, const LettuceEngine::Math::Vector2& halfSize);
        static void DrawRectangleLines(const LettuceEngine::Math::Vector2& center, const LettuceEngine::Math::Color& color, const LettuceEngine::Math::Vector2& halfSize);
        static void DrawText(const std::string text, const LettuceEngine::Math::Vector2& point, const int size, const LettuceEngine::Math::Color& color);
        static void DrawText(const std::string text, const LettuceEngine::Math::Vector2& point, float size, float spacing, const LettuceEngine::Math::Color& color);

        // Utility
        static LettuceEngine::CollisionSystem::AABB MeasureText(const std::string text, float size, float spacing);
};