#include "Assets/Texture2DAsset.h"
#include "Assets/Managers/AssetFactory.h"
REGISTER_ASSET(Texture2DAsset);

using json = nlohmann::json;

Texture2DAsset::Texture2DAsset() : Asset() {}
Texture2DAsset::Texture2DAsset(std::string id) : Asset(id) {}

Texture2DAsset::Texture2DAsset(ImageAsset* image, std::string id) : Texture2DAsset(id) {
    _image = image;
}

Texture2DAsset::~Texture2DAsset() {}

ImageAsset* Texture2DAsset::GetImageAsset() {
    return _image;
}

void Texture2DAsset::SaveToJson(json& j) const {
    Asset::SaveToJson(j);
    json imageJson;
    _image->SaveToJson(imageJson);
    j["image"] = imageJson;
}

void Texture2DAsset::LoadFromJson(const json& data) {
    Asset::LoadFromJson(data);
    _image = new ImageAsset("");
    _image->LoadFromJson(data.at("image"));
}