#include "LettuceEngine/Drawing/BasicDrawing.h"
#include "Raylib/raylib.h"
#include "LettuceEngine/Engine.h"
#include "LettuceEngine/Assets/Managers/RaylibAssetManager.h"

using LColor = LettuceEngine::Math::Color;
using LVector2 = LettuceEngine::Math::Vector2;
using RColor = ::Color;

RColor ConvertEngineColor(const LColor& color) {
    RColor c = {color.R, color.G, color.B, color.A};
    return c;
}

bool CanDraw() {
    return LettuceEngine::Engine::IsRunning();
}

void BasicDrawing::DrawPixel(const LVector2& point, const LColor& color) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    ::DrawPixel(point.X, point.Y, c);
}

void BasicDrawing::DrawCircle(const LVector2& center, const LColor& color, const float radius) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    ::DrawCircle(center.X, center.Y, radius, c);
}

void BasicDrawing::DrawElipse(const LVector2& center, const LColor& color, const LVector2& radius) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    ::DrawEllipse(center.X, center.Y, radius.X, radius.Y, c);
}

void BasicDrawing::DrawRectangle(const LVector2 &center, const LColor &color, const LVector2 &halfSize, const float rotation) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    ::DrawRectanglePro(::Rectangle({center.X - halfSize.X, center.Y - halfSize.Y, halfSize.X * 2, halfSize.Y * 2}), 
        ::Vector2(), rotation, c);
}

void BasicDrawing::DrawRectangleLines(const LVector2 &center, const LColor &color, const LVector2 &halfSize) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    ::DrawRectangleLines(center.X - halfSize.X, center.Y - halfSize.Y, halfSize.X * 2, halfSize.Y * 2, c);
}

void BasicDrawing::DrawText(const std::string text, const LVector2& point, const int size, const LColor& color) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    ::DrawText(text.data(), point.X, point.Y, size, c);
}

void BasicDrawing::DrawText(const std::string text, const LVector2& point, float size, float spacing, const LColor& color, const float rotation) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    ::DrawTextPro(::GetFontDefault(), text.data(), ::Vector2({point.X, point.Y}), 
        ::Vector2(), rotation, size, spacing, c);
}

void BasicDrawing::DrawTexture(const LVector2& point, Texture2DAsset* texture, const LColor& color, const float rotation) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    Texture2D tex = RaylibAssetManager::GetTexture2DData(texture);
    ::DrawTextureEx(tex, ::Vector2({point.X, point.Y}), rotation, 1, c);
}

LettuceEngine::CollisionSystem::AABB BasicDrawing::MeasureText(const std::string text, float size, float spacing) {
    ::Vector2 rVector = ::MeasureTextEx(::GetFontDefault(), text.data(), size, spacing);
    return LettuceEngine::CollisionSystem::AABB(LVector2(rVector.x, rVector.y)/2, LVector2());
}