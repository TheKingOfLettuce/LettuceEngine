#include "LettuceEngine/Assets/Texture2DAsset.h"
#include "LettuceEngine/Assets/Managers/AssetFactory.h"
#include "LettuceEngine/Assets/Managers/RaylibAssetManager.h"
REGISTER_ASSET(Texture2DAsset);

using json = nlohmann::json;
using LColor = LettuceEngine::Math::Color;
using LVector2 = LettuceEngine::Math::Vector2;

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

std::vector<std::pair<const LColor, const LVector2>> Texture2DAsset::GetColorData() const {
    std::vector<std::pair<const LColor, const LVector2>> toReturn = std::vector<std::pair<const LColor, const LVector2>>();
    Texture2D tex = RaylibAssetManager::GetTexture2DData(this);
    Image img = ::LoadImageFromTexture(tex);
    ::Color* colors = static_cast<::Color*>(img.data);
    for(int y = img.height-1; y >= 0; y--) {
        for (int x = 0; x < img.width; x++) {
            ::Color c = *colors;
            colors++;

            toReturn.push_back(std::pair<LColor, LVector2>(LColor(c.r, c.g, c.b, c.a), LVector2(x, y)));
        }
    }
    ::UnloadImage(img);

    if (toReturn.empty()) {
        Log::Error("Could not find any pixels in texture: " + _assetID);
    }
    return toReturn;
}