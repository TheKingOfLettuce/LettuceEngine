#pragma once

#include "Assets/ImageAsset.h"
#include "Assets/Texture2DAsset.h"
#include "Engine.h"
#include "Assets/Managers/AssetTypeCollection.h"
#include <unordered_map>

class AssetManager {
    friend LettuceEngine::Engine;

    public:
        static bool AddImageAsset(ImageAsset* asset);
        static ImageAsset* GetImageAsset(std::string id);
        static bool RemoveImageAsset(ImageAsset* asset);
        static ImageAsset* RemoveImageAsset(std::string id);
        static bool HasImageAsset(ImageAsset* asset);
        static bool HasImageAsset(std::string id);

        static bool AddTexture2DAsset(Texture2DAsset* asset);
        static Texture2DAsset* GetTexture2DAsset(std::string id);
        static bool RemoveTexture2DAsset(Texture2DAsset* asset);
        static Texture2DAsset* RemoveTexture2DAsset(std::string id);
        static bool HasTexture2DAsset(Texture2DAsset* asset);
        static bool HasTexture2DAsset(std::string id);

        template <typename T>
        static bool AddAsset(T* asset) {
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                _assets.emplace(typeID, AssetTypeCollection<T>());
            }

            AssetTypeCollection<T> collection = static_cast<AssetTypeCollection<T>>(_assets.at(typeID));
            return collection.AddAsset(asset);
        }
        template <typename T>
        static T* GetAsset(std::string id) {
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return nullptr;
            }

            AssetTypeCollection<T> collection = static_cast<AssetTypeCollection<T>>(_assets.at(typeID));
            return collection.GetAsset(id);
        }
        template <typename T>
        static bool RemoveAsset(T* asset) {
            return RemoveAsset<T>(asset->GetAssetID()) == nullptr;
        }
        template <typename T>
        static T* RemoveAsset(std::string id) {
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return nullptr;
            }

            AssetTypeCollection<T> collection = static_cast<AssetTypeCollection<T>>(_assets.at(typeID));
            return collection.RemoveAsset(id);
        }
        template <typename T>
        static bool HasAsset(T* asset) {
            return HasAsset<T>(asset.GetAssetID());
        }
        template <typename T>
        static bool HasAsset(std::string id) {
            size_t typeID = typeid(T).hash_code();
            if (!HasAssetType(typeID)) {
                return false;
            }

            AssetTypeCollection<T> collection = static_cast<AssetTypeCollection<T>>(_assets.at(typeID));
            collection.HasAsset(id);
        }

        static void UnloadAllAssets();
        static void UnloadAllTexture2DAssets();
        static void UnloadAllImageAssets();

    private:
        static void LoadRaylibData();
        static void LoadTexture2DRaylibData();

        static void UnloadRaylibData();
        static void UnloadTexture2DRaylibData();

        template <typename T>
        static bool HasAssetTyoe() {
            return HasAssetType(typeid(T).hash_code());
        }
        static bool HasAssetType(size_t typeID);
        static std::unordered_map<size_t, AssetCollection> _assets;

    template <typename T>
    class RaylibAssetCollection : AssetTypeCollection<T> {
        RaylibAssetCollection();
        ~RaylibAssetCollection();
    };
};