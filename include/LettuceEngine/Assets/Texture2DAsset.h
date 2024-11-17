#pragma once
#include "LettuceEngine/Assets/ImageAsset.h"
#include <vector>

class Texture2DAsset : public Asset {
    public:
        Texture2DAsset();
        Texture2DAsset(std::string id);
        Texture2DAsset(ImageAsset* image, std::string id);
        ~Texture2DAsset();

        ImageAsset* GetImageAsset() const;
        int Width() const;
        int Height() const;
        const std::vector<LettuceEngine::Math::Color> Colors() const;

        void SaveToJson(nlohmann::json& j) const override;
        void LoadFromJson(const nlohmann::json& data) override;
    private:
        ImageAsset* _image;
};