#pragma once
#include "Assets/Asset.h"
#include <unordered_map>
#include <vector>

class AssetCollection {
    public:
        AssetCollection();
        ~AssetCollection();

        bool AddAsset(Asset* asset);
        bool RemoveAsset(Asset* asset);
        template <typename T>
        T RemoveAsset(std::string id) {
            if (!HasAsset(id)) {
                return nullptr;
            }

            T toReturn = static_cast<T>(_assets.at(id));
            _assets.erase(id);
            return toReturn;
        }
        bool HasAsset(Asset* asset);
        bool HasAsset(std::string id);
        template <typename T> 
        T GetAsset(std::string id) {
            if (!HasAsset(id)) {
                return nullptr;
            }

            return static_cast<T>(_assets.at(id));
        }
        template <typename T>
        std::vector<T> GetAllAssets() {
            std::vector<T> toReturn = std::vector<T>();
            for (const auto& pair : _assets) {
                toReturn.insert(static_cast<T>(pair.second));
            }

            return toReturn;
        }
    private:
        std::unordered_map<std::string, Asset*> _assets;
};