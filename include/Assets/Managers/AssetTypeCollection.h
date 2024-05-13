#pragma once
#include "Assets/Managers/AssetCollection.h"

template <typename T>
class AssetTypeCollection : public AssetCollection {
    public:
        AssetTypeCollection() : AssetCollection() {}
        ~AssetTypeCollection() {}

        bool AddAsset(T* asset) {
            return AssetCollection::AddAsset(asset);
        }

        bool AddAsset(Asset* asset) {
            if (typeid(asset) == typeid(T*))
                return false;
            return AssetCollection::AddAsset(asset);
        }

        bool RemoveAsset(Asset* asset) {
            if (typeid(asset) == typeid(T*))
                return false;
            return AssetCollection::RemoveAsset(asset);
        }

        bool HasAsset(Asset* asset) {
            if (typeid(asset) == typeid(T*))
                return false;
            return AssetCollection::HasAsset(asset);
        }

        using AssetCollection::HasAsset;

        T* RemoveAsset(std::string id) {
            return static_cast<T*>(AssetCollection::RemoveAsset(id));
        }

        T* GetAsset(std::string id) {
            return static_cast<T*>(AssetCollection::GetAsset(id));
        }

        std::vector<T*> GetAllAssets() {
            std::vector<T*> toReturn = std::vector<T*>();
            for (const auto& pair : _assets) {
                toReturn.push_back(static_cast<T*>(pair.second));
            }

            return toReturn;
        }
};