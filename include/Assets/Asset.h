#pragma once
#include <string>

class Asset {
    public:
        Asset(std::string id);
        ~Asset();

        std::string GetAssetID();
    protected:
        std::string _assetID;
};
