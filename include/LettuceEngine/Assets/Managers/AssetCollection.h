#pragma once
#include "LettuceEngine/Assets/Asset.h"
#include <unordered_map>
#include <vector>

class AssetCollection {
    public:
        AssetCollection();
        virtual ~AssetCollection();

        virtual bool AddAsset(Asset* asset);
        virtual bool RemoveAsset(Asset* asset);
        virtual Asset* RemoveAsset(std::string id);
        virtual bool HasAsset(Asset* asset) const;
        virtual bool HasAsset(std::string id) const;
        virtual Asset* GetAsset(std::string id) const;
        const std::vector<Asset*> GetAllAssets() const;
        virtual size_t GetAssetType() const;

        void SaveToJson(nlohmann::json& j) const;
        void LoadFromJson(const nlohmann::json& data);
    protected:
        std::unordered_map<std::string, Asset*> _assets;
};