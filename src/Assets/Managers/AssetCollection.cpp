#include "Assets/Managers/AssetCollection.h"
#include <stdexcept>
#include "Assets/Managers/AssetFactory.h"

AssetCollection::AssetCollection() {
    _assets = std::unordered_map<std::string, Asset*>();
}

AssetCollection::~AssetCollection() {
    for(const auto& pair : _assets) {
        delete pair.second;
    }
}

bool AssetCollection::AddAsset(Asset* asset) {
    if (asset == nullptr) {
        throw std::invalid_argument("Provided asset is null");
    }
    std::string id = asset->GetAssetID();
    if (HasAsset(id)) {
        return false;
    }

    _assets.emplace(id, asset);
    return true;
}

bool AssetCollection::RemoveAsset(Asset* asset) {
    if (asset == nullptr) {
        throw std::invalid_argument("Provided asset is null");
    }
    std::string id = asset->GetAssetID();
    if (!HasAsset(id) || GetAsset(id) != asset) {
        return false;
    }
    return RemoveAsset(id);
}

Asset* AssetCollection::RemoveAsset(std::string id) {
    if (!HasAsset(id)) {
        return nullptr;
    }

    Asset* toReturn = _assets.at(id);
    _assets.erase(id);
    return toReturn;
}

bool AssetCollection::HasAsset(Asset* asset) const {
    if (asset == nullptr) {
        throw std::invalid_argument("Provided asset is null");
    }
    return HasAsset(asset->GetAssetID());
}

bool AssetCollection::HasAsset(std::string id) const {
    return _assets.find(id) != _assets.end();
}

Asset* AssetCollection::GetAsset(std::string id) const {
    if (!HasAsset(id)) {
        return nullptr;
    }

    return _assets.at(id);
}

const std::vector<Asset*> AssetCollection::GetAllAssets() const {
    std::vector<Asset*> toReturn = std::vector<Asset*>();
    for (const auto& pair : _assets) {
        toReturn.push_back(pair.second);
    }

    return toReturn;
}

using json = nlohmann::json;

void AssetCollection::SaveToJson(json& j) const {
    std::vector<std::pair<std::string, json>> assetPairs = std::vector<std::pair<std::string, json>>();
    for (const auto& pair : _assets) {
        const std::string assetName = Factory<Asset>::GetSaveName(typeid(pair.second).hash_code());
        if (assetName.empty()) {
            Log::Info("Asset is not in the AssetFactory and cannot be persisted " + pair.first);
            continue;
        }
        json assetData = json();
        pair.second->SaveToJson(assetData);
        assetPairs.push_back(std::pair<std::string, json>(assetName, assetData));
    }

    j["assetPairs"] = assetPairs;
}

void AssetCollection::LoadFromJson(const json& data) {
    std::vector<std::pair<std::string, json>> assetPairs = data.at("assetPairs");
    for (const auto& pair : assetPairs) {
        Asset* persistedAsset = Factory<Asset>::Create(pair.first);
        if (persistedAsset == nullptr)
            continue;
        persistedAsset->LoadFromJson(pair.second);
        if (!AddAsset(persistedAsset)) {
            Log::Warning("Failed to restore asset: " + persistedAsset->GetAssetID());
        }
    }
}