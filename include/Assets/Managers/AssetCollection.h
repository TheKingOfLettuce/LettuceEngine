#pragma once
#include "Assets/Asset.h"
#include <unordered_map>
#include <vector>

class AssetCollection {
    public:
        AssetCollection();
        virtual ~AssetCollection();

        bool AddAsset(Asset* asset);
        bool RemoveAsset(Asset* asset);
        Asset* RemoveAsset(std::string id);
        bool HasAsset(Asset* asset);
        bool HasAsset(std::string id);
        Asset* GetAsset(std::string id);
        std::vector<Asset*> GetAllAssets();

    protected:
        std::unordered_map<std::string, Asset*> _assets;
};