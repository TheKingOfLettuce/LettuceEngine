#include "LettuceEngine/Components/Render/PrimitiveRenderer.h"
#include "LettuceEngine/Components/ComponentFactory.h"
#include "LettuceEngine/Drawing/BasicDrawing.h"
REGISTER_COMPONENT(PrimitiveRenderer)

using json = nlohmann::json;
using LettuceEngine::Math::Color;
using LettuceEngine::Math::Vector2;

PrimitiveRenderer::PrimitiveRenderer() : Component() {}

PrimitiveRenderer::~PrimitiveRenderer() {}

PrimitiveRenderer::Shape PrimitiveRenderer::GetShape() const {
    return _renderShape;
}

Color PrimitiveRenderer::GetColor() const {
    return _color;
}

float PrimitiveRenderer::GetSize() const {
    return _size;
}

void PrimitiveRenderer::SetShape(Shape shape) {
    _renderShape = shape;
}

void PrimitiveRenderer::SetColor(Color color) {
    _color = color;
}

void PrimitiveRenderer::SetSize(float size) {
    _size = size;
}

void PrimitiveRenderer::SaveToJson(json& j) {
    Component::SaveToJson(j);
    j["shape"] = _renderShape;
    j["color"] = _color;
    j["size"] = _size;
}

void PrimitiveRenderer::LoadFromJson(const json& data) {
    _renderShape = (Shape)data.at("shape");
    _color = data.at("color");
    _size = data.at("size");
    Component::LoadFromJson(data);
}

void PrimitiveRenderer::Render(RenderMessage* message) {
    Vector2 pos = _lettuce->Position();
    switch (_renderShape) {
        case (Shape::PIXEL):
            BasicDrawing::DrawPixel(pos, _color);
            break;
        case (Shape::CIRCLE):
            BasicDrawing::DrawCircle(pos, _color, _size/2 * _lettuce->Scale().X);
            break;
        case (Shape::ELLIPSE):
            BasicDrawing::DrawElipse(pos, _color, Vector2(_size/4 * _lettuce->Scale().X,  _size/2 * _lettuce->Scale().Y));
            break;
        case (Shape::RECTANGLE):
            BasicDrawing::DrawRectangle(pos, _color, Vector2(_size/2  * _lettuce->Scale().X, _size/2 * _lettuce->Scale().Y), _lettuce->Rotation());
            break;
    }
}