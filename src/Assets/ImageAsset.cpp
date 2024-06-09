#include "LettuceEngine/Assets/ImageAsset.h"
#include "LettuceEngine/Assets/Managers/AssetFactory.h"
REGISTER_ASSET(ImageAsset);

using json = nlohmann::json;

ImageAsset::ImageAsset() : Asset() {}
ImageAsset::ImageAsset(std::string id) : Asset(id) {}

ImageAsset::ImageAsset(std::string filePath, std::string id) : ImageAsset(id) {
    _filePath = filePath;
}

ImageAsset::~ImageAsset() {}

std::string ImageAsset::GetFilePath() {return _filePath;}

void ImageAsset::SaveToJson(json& j) const {
    Asset::SaveToJson(j);
    j["filePath"] = _filePath;
}

void ImageAsset::LoadFromJson(const json& data) {
    Asset::LoadFromJson(data);
    _filePath = data.at("filePath");
}