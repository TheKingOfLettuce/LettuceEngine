#pragma once

#include "Assets/ImageAsset.h"


struct ImageData {
    void *data;
    int width;
    int height;
    int mipmaps;
    int format;
};

class AssetManager {
    public:
        static bool AddImageAsset(ImageAsset* asset);
        static ImageAsset* RemoveImageAsset(ImageAsset* asset);
        static ImageAsset* RemoveImageAsset(std::string id);

        static const ImageData* GetImageData(ImageAsset* asset);
        static const ImageData* GetImageData(std::string id);
};