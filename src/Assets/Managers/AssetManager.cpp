#include "Assets/Managers/AssetManager.h"
#include "Assets/Managers/RaylibAssetManager.h"
#include "Assets/Managers/AssetTypeCollection.h"
#include "Engine.h"
#include "Assets/Managers/AssetCollectionFactory.h"
REGISTER_ASSET_COLLECTION(ImageAssetCollection);
REGISTER_ASSET_COLLECTION(Texture2DAssetCollection);

ImageAssetCollection::ImageAssetCollection() : AssetTypeCollection<ImageAsset>() {}

bool ImageAssetCollection::AddAsset(ImageAsset* asset) {
    bool added = AssetTypeCollection::AddAsset(asset);
    if (added)
        RaylibAssetManager::AddImageAsset(asset);
    return added;
}

ImageAsset* ImageAssetCollection::RemoveAsset(std::string id) {
    ImageAsset* removed = AssetTypeCollection::RemoveAsset(id);
    if (removed)
        RaylibAssetManager::RemoveImageData(id);
    return removed;
}

Texture2DAssetCollection::Texture2DAssetCollection() : AssetTypeCollection<Texture2DAsset>() {}

bool Texture2DAssetCollection::AddAsset(Texture2DAsset* asset) {
    bool added = AssetTypeCollection::AddAsset(asset);
    if (added && LettuceEngine::Engine::IsRunning())
        RaylibAssetManager::AddTexture2DAsset(asset);
    return added;
}

Texture2DAsset* Texture2DAssetCollection::RemoveAsset(std::string id) {
    Texture2DAsset* removed = AssetTypeCollection::RemoveAsset(id);
    if (removed)
        RaylibAssetManager::RemoveTexture2DData(id);
    return removed;
}

std::unordered_map<size_t, AssetCollection*> AssetManager::_assets = std::unordered_map<size_t, AssetCollection*>
{
    {typeid(ImageAsset).hash_code(), new ImageAssetCollection()},
    {typeid(Texture2DAsset).hash_code(), new Texture2DAssetCollection()}
};

void AssetManager::UnloadAllAssets() {
    for(auto& pair : _assets) {
        delete pair.second;
    }
    _assets.clear();
    // add engine level asset collections here
    _assets.emplace(typeid(ImageAsset).hash_code(), new ImageAssetCollection());
    _assets.emplace(typeid(Texture2DAsset).hash_code(), new Texture2DAssetCollection());
}

bool AssetManager::HasAssetType(size_t typeID) {
    return _assets.find(typeID) != _assets.end();
}