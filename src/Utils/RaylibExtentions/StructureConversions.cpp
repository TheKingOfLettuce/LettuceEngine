#include "Utils/RaylibExtentions/StructureConversions.h"

Image StructureConversion::ToRaylibImage(const ImageData* data) {
    Image toReturn;
    toReturn.data = data->data;
    toReturn.format = data->format;
    toReturn.width = data->width;
    toReturn.height = data->height;
    toReturn.mipmaps = data->mipmaps;

    return toReturn;
}

ImageData* StructureConversion::ToLettuceImage(Image data) {
    ImageData* toReturn = new ImageData();
    toReturn->data = data.data;
    toReturn->format = data.format;
    toReturn->width = data.width;
    toReturn->height = data.height;
    toReturn->mipmaps = data.mipmaps;

    return toReturn;
}

Texture2D StructureConversion::ToRaylibTexture2D(const Texture2DData* data) {
    Texture2D toReturn;
    toReturn.id = data->id;
    toReturn.format = data->format;
    toReturn.width = data->width;
    toReturn.height = data->height;
    toReturn.mipmaps = data->mipmaps;

    return toReturn;
}

Texture2DData* StructureConversion::ToLettuceTexture2D(Texture2D data) {
    Texture2DData* toReturn = new Texture2DData();
    toReturn->id = data.id;
    toReturn->format = data.format;
    toReturn->width = data.width;
    toReturn->height = data.height;
    toReturn->mipmaps = data.mipmaps;

    return toReturn;
}