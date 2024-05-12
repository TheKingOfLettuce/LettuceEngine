#pragma once

#include "Assets/ImageAsset.h"
#include "Assets/Texture2DAsset.h"
#include "Engine.h"

class AssetManager {
    friend LettuceEngine::Engine;

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

        static void UnloadAllAssets();
        static void UnloadAllTexture2DAssets();
        static void UnloadAllImageAssets();

    private:
        static void LoadAssetData();
        static void LoadTexture2DData();
};