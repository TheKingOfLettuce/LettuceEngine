#pragma once
#include "Assets/Managers/AssetCollection.h"

template <typename T>
class AssetTypeCollection : public AssetCollection {
    static_assert(std::is_base_of<Asset, T>{},
    "AssetTypeCollection Type must be of type Asset");
    public:
        AssetTypeCollection() : AssetCollection() {}
        ~AssetTypeCollection() {}

        bool AddAsset(Asset* asset) override {
            return AddAsset(static_cast<T*>(asset));
        }

        const std::vector<T*> GetAllAssets() const {
            std::vector<T*> toReturn = std::vector<T*>();
            for (const auto& pair : _assets) {
                toReturn.push_back(static_cast<T*>(pair.second));
            }

            return toReturn;
        }

    protected:
        virtual bool AddAsset(T* asset) {
            return AssetCollection::AddAsset(asset);
        }
};