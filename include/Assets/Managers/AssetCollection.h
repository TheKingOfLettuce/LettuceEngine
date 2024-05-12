#pragma once
#include "Assets/Asset.h"
#include <unordered_map>
#include <vector>

template <typename T>
class AssetCollection {
    public:
        AssetCollection();
        ~AssetCollection();

        bool AddAsset(T asset);
        bool RemoveAsset(Asset* asset);
        T RemoveAsset(std::string id);
        bool HasAsset(Asset* asset);
        bool HasAsset(std::string id); 
        T GetAsset(std::string id);
        std::vector<T> GetAllAssets();
    private:
        std::unordered_map<std::string, T> _assets;
};