#include "Assets/Managers/AssetCollection.h"

AssetCollection::AssetCollection() {
    _assets = std::unordered_map<std::string, Asset*>();
}

AssetCollection::~AssetCollection() {}

bool AssetCollection::AddAsset(Asset* asset) {
    std::string id = asset->GetAssetID();
    if (HasAsset(id)) {
        return false;
    }

    _assets.emplace(id, asset);
    return true;
}

bool AssetCollection::RemoveAsset(Asset* asset) {
    return RemoveAsset<Asset*>(asset->GetAssetID()) != nullptr;
}

bool AssetCollection::HasAsset(Asset* asset) {
    return HasAsset(asset->GetAssetID());
}

bool AssetCollection::HasAsset(std::string id) {
    return _assets.find(id) != _assets.end();
}