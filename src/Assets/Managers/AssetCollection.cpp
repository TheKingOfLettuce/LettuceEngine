#include "Assets/Managers/AssetCollection.h"

template <typename T>
AssetCollection<T>::AssetCollection() {
    _assets = std::unordered_map<std::string, T*>();
}

template <typename T>
AssetCollection<T>::~AssetCollection() {

}

template <typename T>
bool AssetCollection<T>::AddAsset(T* asset) {
    std::string id = asset.GetAssetID();
    if (HasAsset(id)) {
        return false;
    }

    _assets.emplace(id, asset);
    return true;
}

template <typename T>
bool AssetCollection<T>::RemoveAsset(Asset* asset) {
    return RemoveAsset(asset->GetAssetID()) != nullptr;
}

template <typename T>
T* AssetCollection<T>::RemoveAsset(std::string id) {
    if (!HasAsset(id)) {
        return nullptr;
    }

    T* toReturn = _assets.at(id);
    _assets.erase(id);
    return toReturn;
}

template <typename T>
bool AssetCollection<T>::HasAsset(Asset* asset) {
    return HasAsset(asset->GetAssetID());
}

template <typename T>
bool AssetCollection<T>::HasAsset(std::string id) {
    return _assets.find(id) != _assets.end();
}

template <typename T>
T* AssetCollection<T>::GetAsset(std::string id) {
    if (!HasAsset(id)) {
        return nullptr;
    }

    return _assets.at(id);
}