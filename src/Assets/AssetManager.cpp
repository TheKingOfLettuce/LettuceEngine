#include "Assets/AssetManager.h"
#include "Raylib/raylib.h"
#include <unordered_map>

static std::unordered_map<std::string, ImageData*> _imageData = std::unordered_map<std::string, ImageData*>(); 
static std::unordered_map<std::string, ImageAsset*> _imageAssets = std::unordered_map<std::string, ImageAsset*>(); 

bool AssetManager::AddImageAsset(ImageAsset* asset) {
    if (_imageAssets.find(asset->GetAssetID()) == _imageAssets.end()) {
        // collision
        return false;
    }

    _imageAssets.emplace(asset->GetAssetID(), asset);
    _imageData.emplace(asset->GetAssetID(), ToLettuceImage(::LoadImage(asset->GetFilePath().c_str())));
    return true;
}

ImageAsset* AssetManager::RemoveImageAsset(ImageAsset* asset) {
    return RemoveImageAsset(asset->GetAssetID());
}

ImageAsset* AssetManager::RemoveImageAsset(std::string id) {
    if (_imageAssets.find(id) == _imageAssets.end()) {
        return nullptr;
    }

    ImageData* image = _imageData.at(id);
    ImageAsset* toReturn = _imageAssets.at(id);
    _imageAssets.erase(id);
    _imageData.erase(id);
    ::UnloadImage(ToRaylibImage(image));

    return toReturn;
}

const ImageData* AssetManager::GetImageData(ImageAsset* asset) {
    return GetImageData(asset->GetAssetID());
}

const ImageData* AssetManager::GetImageData(std::string id) {
    if (_imageData.find(id) == _imageData.end()) {
        return nullptr;
    }

    return _imageData.at(id);
}

Image ToRaylibImage(ImageData* data) {
    Image toReturn;
    toReturn.data = data->data;
    toReturn.format = data->format;
    toReturn.width = data->width;
    toReturn.height = data->height;
    toReturn.mipmaps = data->mipmaps;

    return toReturn;
}

ImageData* ToLettuceImage(Image data) {
    ImageData* toReturn = new ImageData();
    toReturn->data = data.data;
    toReturn->format = data.format;
    toReturn->width = data.width;
    toReturn->height = data.height;
    toReturn->mipmaps = data.mipmaps;

    return toReturn;
}