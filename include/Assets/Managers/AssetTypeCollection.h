#pragma once
#include "Assets/Managers/AssetCollection.h"

template <typename T>
class AssetTypeCollection : public AssetCollection {
    static_assert(std::is_base_of<Asset, T>{},
    "AssetTypeCollection Type must be of type Asset");
    public:
        AssetTypeCollection() : AssetCollection() {}
        ~AssetTypeCollection() {}

        virtual bool AddAsset(T* asset) {
            return AssetCollection::AddAsset(asset);
        }

        virtual bool HasAsset(T* asset) {
            return AssetCollection::HasAsset(asset);
        }

        virtual bool HasAsset(std::string id) {
            return AssetCollection::HasAsset(id);
        }

        virtual bool RemoveAsset(T* asset) {
            return AssetCollection::RemoveAsset(asset);
        }

        virtual T* RemoveAsset(std::string id) {
            return static_cast<T*>(AssetCollection::RemoveAsset(id));
        }

        virtual T* GetAsset(std::string id) {
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