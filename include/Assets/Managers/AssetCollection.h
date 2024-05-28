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
        bool HasAsset(Asset* asset) const;
        bool HasAsset(std::string id) const;
        Asset* GetAsset(std::string id) const;
        const std::vector<Asset*> GetAllAssets() const;

        void SaveToJson(nlohmann::json& j) const;
        void LoadFromJson(const nlohmann::json& data);
    protected:
        std::unordered_map<std::string, Asset*> _assets;
};