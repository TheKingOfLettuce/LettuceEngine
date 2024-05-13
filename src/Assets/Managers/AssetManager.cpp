#include "Assets/Managers/AssetManager.h"
#include "Assets/Managers/RaylibAssetManager.h"
#include "Assets/Managers/AssetTypeCollection.h"
 
static AssetTypeCollection<ImageAsset> _imageAssets = AssetTypeCollection<ImageAsset>();
static AssetTypeCollection<Texture2DAsset> _texture2DAssets = AssetTypeCollection<Texture2DAsset>();

bool AssetManager::AddImageAsset(ImageAsset* asset) {
    bool added = _imageAssets.AddAsset(asset);
    if (added)
        RaylibAssetManager::AddImageAsset(asset);
    return added;
}

ImageAsset* AssetManager::GetImageAsset(std::string id) {
    return _imageAssets.GetAsset(id);
}

bool AssetManager::RemoveImageAsset(ImageAsset* asset) {
    return RemoveImageAsset(asset->GetAssetID()) != nullptr;
}

ImageAsset* AssetManager::RemoveImageAsset(std::string id) {
    ImageAsset* toReturn = _imageAssets.RemoveAsset(id);
    if (toReturn != nullptr)
        RaylibAssetManager::RemoveImageData(id);
    return toReturn;
}

bool AssetManager::HasImageAsset(ImageAsset* asset) {
    return _imageAssets.HasAsset(asset);
}

bool AssetManager::HasImageAsset(std::string id) {
    return _imageAssets.HasAsset(id);
}

bool AssetManager::AddTexture2DAsset(Texture2DAsset* asset) {
    bool added = _texture2DAssets.AddAsset(asset);
    if (added && LettuceEngine::Engine::IsRunning())
        RaylibAssetManager::AddTexture2DAsset(asset);
    return added;
}

Texture2DAsset* AssetManager::GetTexture2DAsset(std::string id) {
    return _texture2DAssets.GetAsset(id);
}

bool AssetManager::RemoveTexture2DAsset(Texture2DAsset* asset) {
    return RemoveTexture2DAsset(asset->GetAssetID()) != nullptr;
}

Texture2DAsset* AssetManager::RemoveTexture2DAsset(std::string id) {
    Texture2DAsset* toReturn = _texture2DAssets.RemoveAsset(id);
    if (toReturn != nullptr && LettuceEngine::Engine::IsRunning())
        RaylibAssetManager::RemoveTexture2DData(id);
    return toReturn;
}

bool AssetManager::HasTexture2DAsset(Texture2DAsset* asset) {
    return _texture2DAssets.HasAsset(asset);
}

bool AssetManager::HasTexture2DAsset(std::string id) {
    return _texture2DAssets.HasAsset(id);
}

void AssetManager::LoadRaylibData() {
    LoadTexture2DRaylibData();
}

void AssetManager::LoadTexture2DRaylibData() {
    for(Texture2DAsset* asset : _texture2DAssets.GetAllAssets()) {
        RaylibAssetManager::AddTexture2DAsset(asset);
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
    for(ImageAsset* asset : _imageAssets.GetAllAssets()) {
        RemoveImageAsset(asset);
        delete asset;
    }
}

void AssetManager::UnloadAllTexture2DAssets() {
    for(Texture2DAsset* asset : _texture2DAssets.GetAllAssets()) {
        RemoveTexture2DAsset(asset);
        delete asset;
    }
}