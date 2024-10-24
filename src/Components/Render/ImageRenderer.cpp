#include "LettuceEngine/Components/Render/ImageRenderer.h"
#include "LettuceEngine/Components/ComponentFactory.h"
#include "LettuceEngine/Drawing/BasicDrawing.h"
#include "LettuceEngine/Assets/Managers/AssetManager.h"
REGISTER_COMPONENT(ImageRenderer)

using json = nlohmann::json;
using LettuceEngine::Math::Color;
using LettuceEngine::Math::Vector2;

ImageRenderer::ImageRenderer() : Component() {
    _color = Color();
    _texture = nullptr;
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
        BasicDrawing::DrawRectangle(_lettuce->Position(), _color, Vector2(50, 50), _lettuce->Rotation());
        return;
    }
    BasicDrawing::DrawTexture(_lettuce->Position(), _texture, _color, _lettuce->Scale(), _lettuce->Rotation());
}

void ImageRenderer::SaveToJson(json& j) {
    Component::SaveToJson(j);
    j["textureAssetID"] = _texture ? _texture->GetAssetID() : "";
    j["color"] = _color;
}

void ImageRenderer::LoadFromJson(const json& data) {
    std::string assetID = data.at("textureAssetID");
    if (assetID != "")
        _texture = AssetManager::GetAsset<Texture2DAsset>(assetID);
    _color = data.at("color");
    Component::LoadFromJson(data);
}