#pragma once
#include "Assets/Managers/AssetCollection.h"

template <typename T>
class AssetTypeCollection : public AssetCollection {
    static_assert(std::is_base_of<Asset, T>{},
    "AssetTypeCollection Type must be of type Asset");
    public:
        AssetTypeCollection() : AssetCollection() {}
        ~AssetTypeCollection() {}

        bool AddAsset(T* asset) {
            return AssetCollection::AddAsset(asset);
        }

        bool HasAsset(T* asset) {
            return AssetCollection::HasAsset(asset);
        }

        bool HasAsset(std::string id) {
            return AssetCollection::HasAsset(id);
        }

        bool RemoveAsset(T* asset) {
            return AssetCollection::RemoveAsset(asset);
        }

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