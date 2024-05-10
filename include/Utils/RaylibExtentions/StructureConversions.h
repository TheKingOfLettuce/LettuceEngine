#pragma once
#include "Raylib/raylib.h"
#include "Assets/AssetManager.h"

class StructureConversion {
    public:
        static Image ToRaylibImage(const ImageData* data);
        static ImageData* ToLettuceImage(Image data);

        static Texture2D ToRaylibTexture2D(const Texture2DData* data);
        static Texture2DData* ToLettuceTexture2D(Texture2D data);
};