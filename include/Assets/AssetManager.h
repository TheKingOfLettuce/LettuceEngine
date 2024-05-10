#pragma once

#include "Assets/ImageAsset.h"
#include "Assets/Texture2DAsset.h"

struct ImageData {
    void *data;
    int width;
    int height;
    int mipmaps;
    int format;
};

struct Texture2DData {
    unsigned int id;
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

        static bool AddTexture2DAsset(Texture2DAsset* asset);
        static Texture2DAsset* RemoveTexture2DAsset(Texture2DAsset* asset);
        static Texture2DAsset* RemoveTexture2DAsset(std::string id);

        static const ImageData* GetImageData(ImageAsset* asset);
        static const ImageData* GetImageData(std::string id);

        static const Texture2DData* GetTexture2DData(Texture2DAsset* asset);
        static const Texture2DData* GetTexture2DData(std::string id);

        static void UnloadAllData();
        static void UnloadAllTexture2DData();
        static void UnloadAllImageData();
};