#include "Assets/Texture2DAsset.h"

Texture2DAsset::Texture2DAsset(ImageAsset* image, std::string id) : Asset(id) {
    _image = image;
}

Texture2DAsset::~Texture2DAsset() {}

ImageAsset* Texture2DAsset::GetImageAsset() {
    return _image;
}