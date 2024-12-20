#pragma once
#include "LettuceEngine/Assets/ImageAsset.h"

class Texture2DAsset : public Asset {
    public:
        Texture2DAsset();
        Texture2DAsset(std::string id);
        Texture2DAsset(ImageAsset* image, std::string id);
        ~Texture2DAsset();

        ImageAsset* GetImageAsset();
        int Width();
        int Height();

        void SaveToJson(nlohmann::json& j) const override;
        void LoadFromJson(const nlohmann::json& data) override;
    private:
        ImageAsset* _image;
};