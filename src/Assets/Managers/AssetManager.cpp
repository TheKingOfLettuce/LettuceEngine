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

Asset* ImageAssetCollection::RemoveAsset(std::string id) {
    Asset* removed = AssetTypeCollection::RemoveAsset(id);
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

Asset* Texture2DAssetCollection::RemoveAsset(std::string id) {
    Asset* removed = AssetTypeCollection::RemoveAsset(id);
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

bool AssetManager::AddAsset(Asset* asset, bool addDefaultCollection) {
    if (asset == nullptr) {
        throw std::invalid_argument("Provided asset is null");
    }
    size_t typeID = typeid(*asset).hash_code();
    if (!HasAssetType(typeID)) {
        if (!addDefaultCollection) return false;
        AddAssetCollection(new AssetCollection(), typeID);
    }

    return _assets.at(typeID)->AddAsset(asset);
}

bool AssetManager::AddAssetCollection(AssetCollection* collection, size_t assetType) {
    if (collection == nullptr) {
        throw std::invalid_argument("Provided collection is null");
    }
    if (HasAssetType(assetType)) return false;
    _assets.emplace(assetType, collection);
    return true;
}