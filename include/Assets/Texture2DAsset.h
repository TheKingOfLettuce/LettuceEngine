#pragma once
#include "Assets/ImageAsset.h"

class Texture2DAsset : public Asset {
    public:
        Texture2DAsset(ImageAsset* image, std::string id);
        ~Texture2DAsset();

        ImageAsset* GetImageAsset();
    private:
        ImageAsset* _image;
};