#pragma once
#include "LettuceEngine/Assets/ImageAsset.h"
#include "LettuceEngine/Math/Color.h"
#include "LettuceEngine/Math/Vector2.h"
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
        std::vector<std::pair<const LettuceEngine::Math::Color, const LettuceEngine::Math::Vector2>> GetColorData() const;

        void SaveToJson(nlohmann::json& j) const override;
        void LoadFromJson(const nlohmann::json& data) override;
    private:
        ImageAsset* _image;
};