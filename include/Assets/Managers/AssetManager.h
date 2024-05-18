#pragma once

#include "Assets/ImageAsset.h"
#include "Assets/Texture2DAsset.h"
#include "Assets/Managers/AssetTypeCollection.h"
#include <typeinfo>
#include <stdexcept>
#include <unordered_map>

class AssetManager {
    public:
        template <typename T>
        static bool AddAsset(T* asset, bool addDefaultCollection = true) {
            if (asset == nullptr) {
                throw std::invalid_argument("Provided asset is null");
            }
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                if (!addDefaultCollection) return false;
                AddAssetCollection(new AssetTypeCollection<T>());
            }

            AssetTypeCollection<T>* collection = static_cast<AssetTypeCollection<T>*>(_assets.at(typeID));
            return collection->AddAsset(asset);
        }
        template <typename T>
        static T* GetAsset(std::string id) {
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return nullptr;
            }

            AssetTypeCollection<T>* collection = static_cast<AssetTypeCollection<T>*>(_assets.at(typeID));
            return collection->GetAsset(id);
        }
        template <typename T>
        static bool RemoveAsset(T* asset) {
            if (asset == nullptr) {
                throw std::invalid_argument("Provided asset is null");
            }
            return RemoveAsset<T>(asset->GetAssetID()) == nullptr;
        }
        template <typename T>
        static T* RemoveAsset(std::string id) {
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return nullptr;
            }

            AssetTypeCollection<T>* collection = static_cast<AssetTypeCollection<T>*>(_assets.at(typeID));
            return collection->RemoveAsset(id);
        }
        template <typename T>
        static bool HasAsset(T* asset) {
            if (asset == nullptr) {
                throw std::invalid_argument("Provided asset is null");
            }
            return HasAsset<T>(asset.GetAssetID());
        }
        template <typename T>
        static bool HasAsset(std::string id) {
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return false;
            }

            AssetTypeCollection<T>* collection = static_cast<AssetTypeCollection<T>*>(_assets.at(typeID));
            return collection->HasAsset(id);
        }

        template <typename T>
        static bool AddAssetCollection(AssetTypeCollection<T>* collection) {
            if (collection == nullptr) {
                throw std::invalid_argument("Provided collection is null");
            }
            size_t typeID = typeid(T).hash_code();
            if (HasAssetType(typeID)) return false;
            _assets.emplace(typeID, collection);
            return true;
        }

        template <typename T>
        static const AssetTypeCollection<T>* GetAssetCollection() {
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                throw std::invalid_argument("Provided type has never had assets in the manager");
            }

            return static_cast<AssetTypeCollection<T>*>(_assets.at(typeID));
        }

        static void UnloadAllAssets();

    private:
        template <typename T>
        static bool HasAssetTyoe() {
            return HasAssetType(typeid(T).hash_code());
        }
        static bool HasAssetType(size_t typeID);
        static std::unordered_map<size_t, AssetCollection*> _assets;
};

class ImageAssetCollection : public AssetTypeCollection<ImageAsset> {
    public:
        ImageAssetCollection();

        bool AddAsset(ImageAsset* asset) override;
        ImageAsset* RemoveAsset(std::string id) override;
};

class Texture2DAssetCollection : public AssetTypeCollection<Texture2DAsset> {
    public:
        Texture2DAssetCollection();

        bool AddAsset(Texture2DAsset* asset) override;
        Texture2DAsset* RemoveAsset(std::string id) override;
};