#include "Components/Render/ImageRenderer.h"
#include "Drawing/BasicDrawing.h"

using Color = LettuceEngine::Math::Color;

ImageRenderer::ImageRenderer() : Component() {
    _color = Color();
}
ImageRenderer::~ImageRenderer() {}

void ImageRenderer::SetTexture(Texture2DAsset* texture) {
    _texture = texture;
}

Texture2DAsset* ImageRenderer::GetTexture() {
    return _texture;
}

void ImageRenderer::SetColor(Color color) {
    _color = color;
}

Color ImageRenderer::GetColor() {
    return _color;
}

void ImageRenderer::Render(RenderMessage* message) {
    if (_texture == nullptr) {
        BasicDrawing::DrawRectangle(_lettuce->Position(), _color, LettuceEngine::Math::Vector2(50, 50));
    }
    BasicDrawing::DrawTexture(_lettuce->Position(), _texture, _color);
}