#pragma once
#include "Assets/Asset.h"

class ImageAsset : public Asset {
    public:
        ImageAsset(std::string id);
        ImageAsset(std::string filePath, std::string id);
        ~ImageAsset();

        std::string GetFilePath();

        void SaveToJson(nlohmann::json& j) const override;
        void LoadFromJson(const nlohmann::json& data) override;
    private:
        std::string _filePath;
};