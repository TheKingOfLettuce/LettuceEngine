#pragma once

#include "LettuceEngine/Assets/ImageAsset.h"
#include "LettuceEngine/Assets/Texture2DAsset.h"
#include "LettuceEngine/Assets/Managers/AssetTypeCollection.h"
#include <typeinfo>
#include <stdexcept>
#include <unordered_map>

class AssetManager {
    public:
        static bool AddAsset(Asset* asset, bool addDefaultCollection = true);
        template <typename T>
        static T* GetAsset(std::string id) {
            static_assert(std::is_base_of<Asset, T>{},
            "AssetTypeCollection Type must be of type Asset");
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return nullptr;
            }

            return static_cast<T*>(_assets.at(typeID)->GetAsset(id));
        }
        template <typename T>
        static bool RemoveAsset(T* asset) {
            static_assert(std::is_base_of<Asset, T>{},
            "AssetTypeCollection Type must be of type Asset");
            if (asset == nullptr) {
                throw std::invalid_argument("Provided asset is null");
            }
            std::string id = asset->GetAssetID();
            if (!HasAsset<T>(id) || GetAsset<T>(id) != asset) {
                return false;
            }
            return RemoveAsset<T>(id);
        }
        template <typename T>
        static T* RemoveAsset(std::string id) {
            static_assert(std::is_base_of<Asset, T>{},
            "AssetTypeCollection Type must be of type Asset");
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return nullptr;
            }

            return static_cast<T*>(_assets.at(typeID)->RemoveAsset(id));
        }
        template <typename T>
        static bool HasAsset(T* asset) {
            static_assert(std::is_base_of<Asset, T>{},
            "AssetTypeCollection Type must be of type Asset");
            if (asset == nullptr) {
                throw std::invalid_argument("Provided asset is null");
            }
            return HasAsset<T>(asset->GetAssetID());
        }
        template <typename T>
        static bool HasAsset(std::string id) {
            static_assert(std::is_base_of<Asset, T>{},
            "AssetTypeCollection Type must be of type Asset");
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return false;
            }

            return _assets.at(typeID)->HasAsset(id);
        }

        template <typename T>
        static bool AddAssetCollection(AssetCollection* collection) {
            static_assert(std::is_base_of<Asset, T>{},
            "AssetTypeCollection Type must be of type Asset");
            size_t typeID = typeid(T).hash_code();
            return AddAssetCollection(collection, typeID);
        }

        static bool AddAssetCollection(AssetCollection* collection, size_t assetType);

        template <typename T>
        static const AssetCollection* GetAssetCollection() {
            static_assert(std::is_base_of<Asset, T>{},
            "AssetTypeCollection Type must be of type Asset");
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return nullptr;
            }

            return _assets.at(typeID);
        }

        static void UnloadAllAssets();

        static void SaveToJson(nlohmann::json& j);
        static void LoadFromJson(const nlohmann::json& data, bool additive = false);

    private:
        template <typename T>
        static bool HasAssetTyoe() {
            static_assert(std::is_base_of<Asset, T>{},
            "AssetTypeCollection Type must be of type Asset");
            return HasAssetType(typeid(T).hash_code());
        }
        static bool HasAssetType(size_t typeID);
        static void AddEngineCollections();
        static std::unordered_map<size_t, AssetCollection*> _assets;
};

class ImageAssetCollection : public AssetTypeCollection<ImageAsset> {
    public:
        ImageAssetCollection();

        Asset* RemoveAsset(std::string id) override;
    protected:
        bool AddAsset(ImageAsset* asset) override;
};

class Texture2DAssetCollection : public AssetTypeCollection<Texture2DAsset> {
    public:
        Texture2DAssetCollection();

        Asset* RemoveAsset(std::string id) override;
    protected:
        bool AddAsset(Texture2DAsset* asset) override;

};