#include "Assets/ImageAsset.h"

ImageAsset::ImageAsset(std::string filePath, std::string id) : Asset(id) {
    _filePath = filePath;
}

ImageAsset::~ImageAsset() {}

std::string ImageAsset::GetFilePath() {return _filePath;}