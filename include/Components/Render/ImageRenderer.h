#pragma once
#include "Component.h"
#include "Assets/ImageAsset.h"

class ImageRenderer : public Component {
    public:
        ImageRenderer();
        ~ImageRenderer();

        void Render(RenderMessage* message) override;

        void SetImage(ImageAsset* image);

    private:
        ImageAsset* _image;
};