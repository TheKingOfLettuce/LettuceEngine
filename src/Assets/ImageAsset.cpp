#include "Assets/ImageAsset.h"
#include "Assets/Managers/AssetFactory.h"
REGISTER_ASSET(ImageAsset);

ImageAsset::ImageAsset(std::string id) : Asset(id) {}

ImageAsset::ImageAsset(std::string filePath, std::string id) : ImageAsset(id) {
    _filePath = filePath;
}

ImageAsset::~ImageAsset() {}

std::string ImageAsset::GetFilePath() {return _filePath;}