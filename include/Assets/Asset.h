#pragma once
#include <string>
#include "Utils/json.hpp"

class Asset {
    public:
        Asset();
        Asset(std::string id);
        virtual ~Asset();

        std::string GetAssetID();

        void virtual SaveToJson(nlohmann::json& j) const;
        void virtual LoadFromJson(const nlohmann::json& data);
    protected:
        std::string _assetID;
};
