#include "Assets/AssetManager.h"
#include "Raylib/raylib.h"
#include "Assets/RaylibAssetManager.h"
#include <unordered_map>
 
static std::unordered_map<std::string, ImageAsset*> _imageAssets = std::unordered_map<std::string, ImageAsset*>();

static std::unordered_map<std::string, Texture2DAsset*> _texture2DAssets = std::unordered_map<std::string, Texture2DAsset*>();

bool AssetManager::AddImageAsset(ImageAsset* asset) {
    if (_imageAssets.find(asset->GetAssetID()) != _imageAssets.end()) {
        // collision
        return false;
    }

    _imageAssets.emplace(asset->GetAssetID(), asset);
    RaylibAssetManager::AddImageAsset(asset);
    return true;
}

ImageAsset* AssetManager::GetImageAsset(std::string id) {
    if (_imageAssets.find(id) == _imageAssets.end()) {
        // DNE
        return nullptr;
    }

    return _imageAssets.at(id);
}

bool AssetManager::RemoveImageAsset(ImageAsset* asset) {
    return RemoveImageAsset(asset->GetAssetID()) != nullptr;
}

ImageAsset* AssetManager::RemoveImageAsset(std::string id) {
    if (_imageAssets.find(id) == _imageAssets.end()) {
        return nullptr;
    }

    ImageAsset* toReturn = _imageAssets.at(id);
    _imageAssets.erase(id);
    RaylibAssetManager::RemoveImageData(id);

    return toReturn;
}

bool AssetManager::HasImageAsset(ImageAsset* asset) {
    return _imageAssets.find(asset->GetAssetID()) != _imageAssets.end();
}

bool AssetManager::AddTexture2DAsset(Texture2DAsset* asset) {
    if (_texture2DAssets.find(asset->GetAssetID()) != _texture2DAssets.end()) {
        // collision
        return false;
    }

    _texture2DAssets.emplace(asset->GetAssetID(), asset);
    if (LettuceEngine::Engine::IsRunning())
        RaylibAssetManager::AddTexture2DAsset(asset);
    return true;
}

Texture2DAsset* AssetManager::GetTexture2DAsset(std::string id) {
    if (_texture2DAssets.find(id) == _texture2DAssets.end()) {
        // DNE
        return nullptr;
    }

    return _texture2DAssets.at(id);
}

bool AssetManager::RemoveTexture2DAsset(Texture2DAsset* asset) {
    return RemoveTexture2DAsset(asset->GetAssetID()) != nullptr;
}

Texture2DAsset* AssetManager::RemoveTexture2DAsset(std::string id) {
    if (_texture2DAssets.find(id) == _texture2DAssets.end()) {
        return nullptr;
    }

    Texture2DAsset* toReturn = _texture2DAssets.at(id);
    _texture2DAssets.erase(id);
    if (LettuceEngine::Engine::IsRunning())
        RaylibAssetManager::RemoveTexture2DData(id);

    return toReturn;
}

bool AssetManager::HasTexture2DAsset(Texture2DAsset* asset) {
    return _texture2DAssets.find(asset->GetAssetID()) != _texture2DAssets.end();
}

void AssetManager::LoadRaylibData() {
    LoadTexture2DRaylibData();
}

void AssetManager::LoadTexture2DRaylibData() {
    for (const auto& pair : _texture2DAssets) {
        RaylibAssetManager::AddTexture2DAsset(pair.second);
    }
}

void AssetManager::UnloadRaylibData() {
    UnloadTexture2DRaylibData();
}

void AssetManager::UnloadTexture2DRaylibData() {
    RaylibAssetManager::RemoveAllTexture2DData();
}

void AssetManager::UnloadAllAssets() {
    UnloadAllTexture2DAssets();
    UnloadAllImageAssets();
}

void AssetManager::UnloadAllImageAssets() {
    while (!_imageAssets.empty()) {
        ImageAsset* asset = _imageAssets.begin().operator*().second;
        RemoveImageAsset(asset);
        delete asset;
    }
}

void AssetManager::UnloadAllTexture2DAssets() {
    while (!_texture2DAssets.empty()) {
        Texture2DAsset* asset = _texture2DAssets.begin().operator*().second;
        RemoveTexture2DAsset(asset);
        delete asset;
    }
}