#include "Assets/Managers/AssetCollection.h"

AssetCollection::AssetCollection() {
    _assets = std::unordered_map<std::string, Asset*>();
}

AssetCollection::~AssetCollection() {
    for(const auto& pair : _assets) {
        delete pair.second;
    }
}

bool AssetCollection::AddAsset(Asset* asset) {
    std::string id = asset->GetAssetID();
    if (HasAsset(id)) {
        return false;
    }

    _assets.emplace(id, asset);
    return true;
}

bool AssetCollection::RemoveAsset(Asset* asset) {
    return RemoveAsset(asset->GetAssetID()) != nullptr;
}

Asset* AssetCollection::RemoveAsset(std::string id) {
    if (!HasAsset(id)) {
        return nullptr;
    }

    Asset* toReturn = _assets.at(id);
    _assets.erase(id);
    return toReturn;
}

bool AssetCollection::HasAsset(Asset* asset) {
    return HasAsset(asset->GetAssetID());
}

bool AssetCollection::HasAsset(std::string id) {
    return _assets.find(id) != _assets.end();
}

Asset* AssetCollection::GetAsset(std::string id) {
    if (!HasAsset(id)) {
        return nullptr;
    }

    return _assets.at(id);
}

std::vector<Asset*> AssetCollection::GetAllAssets() {
    std::vector<Asset*> toReturn = std::vector<Asset*>();
    for (const auto& pair : _assets) {
        toReturn.push_back(pair.second);
    }

    return toReturn;
}