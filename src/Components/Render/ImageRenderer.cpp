#include "Components/Render/ImageRenderer.h"

ImageRenderer::ImageRenderer() : Component() {}
ImageRenderer::~ImageRenderer() {}

void ImageRenderer::SetImage(ImageAsset* image) {
    _image = image;
}

void ImageRenderer::Render(RenderMessage* message) {
    
}