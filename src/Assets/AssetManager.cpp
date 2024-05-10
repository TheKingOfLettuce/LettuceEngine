#include "Assets/AssetManager.h"
#include "Raylib/raylib.h"
#include "Utils/RaylibExtentions/StructureConversions.h"
#include <unordered_map>

static std::unordered_map<std::string, ImageData*> _imageData = std::unordered_map<std::string, ImageData*>(); 
static std::unordered_map<std::string, ImageAsset*> _imageAssets = std::unordered_map<std::string, ImageAsset*>();

static std::unordered_map<std::string, Texture2DData*> _texture2DData = std::unordered_map<std::string, Texture2DData*>(); 
static std::unordered_map<std::string, Texture2DAsset*> _texture2DAssets = std::unordered_map<std::string, Texture2DAsset*>();

bool AssetManager::AddImageAsset(ImageAsset* asset) {
    if (_imageAssets.find(asset->GetAssetID()) == _imageAssets.end()) {
        // collision
        return false;
    }

    _imageAssets.emplace(asset->GetAssetID(), asset);
    _imageData.emplace(asset->GetAssetID(), StructureConversion::ToLettuceImage(::LoadImage(asset->GetFilePath().c_str())));
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
    ::UnloadImage(StructureConversion::ToRaylibImage(image));

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

bool AssetManager::AddTexture2DAsset(Texture2DAsset* asset) {
    if (_texture2DAssets.find(asset->GetAssetID()) == _texture2DAssets.end()) {
        // collision
        return false;
    }

    _texture2DAssets.emplace(asset->GetAssetID(), asset);
    bool removeImageAfter = false;
    if (_imageData.find(asset->GetImageAsset()->GetAssetID()) == _imageData.end()) {
        removeImageAfter = true;
        AddImageAsset(asset->GetImageAsset());
    }
    Texture2D rayTex = ::LoadTextureFromImage(StructureConversion::ToRaylibImage(GetImageData(asset->GetImageAsset())));
    _texture2DData.emplace(asset->GetAssetID(), StructureConversion::ToLettuceTexture2D(rayTex));
    if (removeImageAfter) {
        RemoveImageAsset(asset->GetImageAsset());
    }
    return true;
}

Texture2DAsset* AssetManager::RemoveTexture2DAsset(Texture2DAsset* asset) {
    return RemoveTexture2DAsset(asset->GetAssetID());
}

Texture2DAsset* AssetManager::RemoveTexture2DAsset(std::string id) {
    if (_texture2DAssets.find(id) == _texture2DAssets.end()) {
        return nullptr;
    }

    Texture2DAsset* toReturn = _texture2DAssets.at(id);
    Texture2DData* data = _texture2DData.at(id);
    _texture2DAssets.erase(id);
    _texture2DData.erase(id);
    ::UnloadTexture(StructureConversion::ToRaylibTexture2D(data));

    return toReturn;
}

const Texture2DData* AssetManager::GetTexture2DData(Texture2DAsset* asset) {
    return GetTexture2DData(asset->GetAssetID());
}

const Texture2DData* AssetManager::GetTexture2DData(std::string id) {
    if (_texture2DData.find(id) == _texture2DData.end()) {
        return nullptr;
    }

    return _texture2DData.at(id);
}