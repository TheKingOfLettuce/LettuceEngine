#include "Assets/Texture2DAsset.h"
#include "Assets/Managers/AssetFactory.h"
REGISTER_ASSET(Texture2DAsset);

Texture2DAsset::Texture2DAsset(std::string id) : Asset(id) {}

Texture2DAsset::Texture2DAsset(ImageAsset* image, std::string id) : Texture2DAsset(id) {
    _image = image;
}

Texture2DAsset::~Texture2DAsset() {}

ImageAsset* Texture2DAsset::GetImageAsset() {
    return _image;
}