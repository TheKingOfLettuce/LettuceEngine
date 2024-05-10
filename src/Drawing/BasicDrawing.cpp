#include "Drawing/BasicDrawing.h"
#include "Raylib/raylib.h"
#include "Engine.h"
#include "Assets/RaylibAssetManager.h"
#include "Utils/RaylibExtentions/StructureConversions.h"

using LColor = LettuceEngine::Math::Color;
using LVector2 = LettuceEngine::Math::Vector2;
using RColor = ::Color;

RColor ConvertEngineColor(const LColor& color) {
    RColor c = {color.R, color.G, color.B, color.A};
    return c;
}

bool CanDraw() {
    LettuceEngine::Engine* engine = LettuceEngine::Engine::GetInstance();
    if (engine == nullptr) return false;
    return engine->IsRunning();
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

void BasicDrawing::DrawRectangle(const LVector2 &center, const LColor &color, const LVector2 &halfSize) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    ::DrawRectangle(center.X - halfSize.X, center.Y - halfSize.Y, halfSize.X * 2, halfSize.Y * 2, c);
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

void BasicDrawing::DrawText(const std::string text, const LVector2& point, float size, float spacing, const LColor& color) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    ::DrawTextEx(::GetFontDefault(), text.data(), ::Vector2({point.X, point.Y}), size, spacing, c);
}

void BasicDrawing::DrawTexture(const LVector2& point, Texture2DAsset* texture, const LColor& color) {
    if (!CanDraw()) return;
    RColor c = ConvertEngineColor(color);
    Texture2D tex = RaylibAssetManager::GetTexture2DData(texture);
    ::DrawTexture(tex, point.X, point.Y, c);
}

LettuceEngine::CollisionSystem::AABB BasicDrawing::MeasureText(const std::string text, float size, float spacing) {
    ::Vector2 rVector = ::MeasureTextEx(::GetFontDefault(), text.data(), size, spacing);
    return LettuceEngine::CollisionSystem::AABB(LVector2(rVector.x, rVector.y)/2, LVector2());
}