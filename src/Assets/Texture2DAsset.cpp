#include "LettuceEngine/Assets/Texture2DAsset.h"
#include "LettuceEngine/Assets/Managers/AssetFactory.h"
#include "LettuceEngine/Assets/Managers/RaylibAssetManager.h"
REGISTER_ASSET(Texture2DAsset);

using json = nlohmann::json;

Texture2DAsset::Texture2DAsset() : Asset() {}
Texture2DAsset::Texture2DAsset(std::string id) : Asset(id) {}

Texture2DAsset::Texture2DAsset(ImageAsset* image, std::string id) : Texture2DAsset(id) {
    _image = image;
}

Texture2DAsset::~Texture2DAsset() {}

ImageAsset* Texture2DAsset::GetImageAsset() const {
    return _image;
}

int Texture2DAsset::Width() const {
    if (!RaylibAssetManager::HasTexture2DData(this)) {
        Log::Error("Cannot get width of texture " + _assetID + ". Texture is not loaded!");
        return -1;
    }
    return RaylibAssetManager::GetTexture2DData(this).width;
}

int Texture2DAsset::Height() const  {
    if (!RaylibAssetManager::HasTexture2DData(this)) {
        Log::Error("Cannot get height of texture " + _assetID + ". Texture is not loaded!");
        return -1;
    }
    return RaylibAssetManager::GetTexture2DData(this).height;
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