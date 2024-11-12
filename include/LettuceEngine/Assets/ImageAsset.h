#pragma once
#include "LettuceEngine/Assets/Asset.h"

class ImageAsset : public Asset {
    public:
        ImageAsset();
        ImageAsset(std::string id);
        ImageAsset(std::string filePath, std::string id);
        ~ImageAsset();

        std::string GetFilePath() const;

        void SaveToJson(nlohmann::json& j) const override;
        void LoadFromJson(const nlohmann::json& data) override;
    private:
        std::string _filePath;
};