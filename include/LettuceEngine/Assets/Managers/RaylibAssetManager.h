#pragma once
#include "Raylib/raylib.h"
#include "LettuceEngine/Assets/ImageAsset.h"
#include "LettuceEngine/Assets/Texture2DAsset.h"
#include "LettuceEngine/Assets/Managers/AssetManager.h"
#include "LettuceEngine/Engine.h"
#include "LettuceEngine/Components/Render/RenderTextureRenderer.h"

class RaylibAssetManager {
    friend AssetManager;
    friend LettuceEngine::Engine;
    friend ImageAssetCollection;
    friend Texture2DAssetCollection;

    public:
        static Image GetImageData(const ImageAsset* asset);
        static Image GetImageData(const std::string id);
        static bool HasImageData(const ImageAsset* asset);
        static bool HasImageData(const std::string id);

        static Texture2D GetTexture2DData(const Texture2DAsset* asset);
        static Texture2D GetTexture2DData(const std::string id); 
        static bool HasTexture2DData(const Texture2DAsset* asset);
        static bool HasTexture2DData(const std::string id); 

        static RenderTexture2D GetRenderTexture2DData(const RenderTextureRenderer* render);
        static bool HasRenderTexture2DData(const RenderTextureRenderer* render);
        static bool AddRenderTexture2DData(const RenderTextureRenderer* render, const RenderTexture2D data);
        static void RemoveRenderTexutre2DData(const RenderTextureRenderer* render);

    private:
        static void LoadAllAssetManagerGPUData();
        static void UnloadAllAssetManagerGPUData();

        static bool AddImageAsset(const ImageAsset* asset);
        static bool AddTexture2DAsset(const Texture2DAsset* asset);

        static void RemoveImageData(const ImageAsset* asset);
        static void RemoveImageData(const std::string id);
        static void RemoveTexture2DData(const Texture2DAsset* asset);
        static void RemoveTexture2DData(const std::string id);

        static void RemoveAllData();
        static void RemoveAllImageData();
        static void RemoveAllTexture2DData();
        static void RemoveAllRenderTexture2DData();
};