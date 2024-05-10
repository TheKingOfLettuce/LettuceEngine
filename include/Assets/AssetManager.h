#pragma once

#include "Assets/ImageAsset.h"
#include "Assets/Texture2DAsset.h"

class AssetManager {
    public:
        static bool AddImageAsset(ImageAsset* asset);
        static ImageAsset* GetImageAsset(std::string id);
        static bool RemoveImageAsset(ImageAsset* asset);
        static ImageAsset* RemoveImageAsset(std::string id);
        static bool HasImageAsset(ImageAsset* asset);

        static bool AddTexture2DAsset(Texture2DAsset* asset);
        static Texture2DAsset* GetTexture2DAsset(std::string id);
        static bool RemoveTexture2DAsset(Texture2DAsset* asset);
        static Texture2DAsset* RemoveTexture2DAsset(std::string id);
        static bool HasTexture2DAsset(Texture2DAsset* asset);

        static void UnloadAllData();
        static void UnloadAllTexture2DData();
        static void UnloadAllImageData();
};