#pragma once

#include "LettuceEngine/Utils/Factory.h"
#include "LettuceEngine/Assets/Asset.h"

template class Factory<Asset>;

template <class T>
class AssetCreator {
static_assert(std::is_base_of<Asset, T>{},
"Provided type must be a Asset");
public:
    explicit AssetCreator(const std::string &name) {
        Log::Info("Registering Asset to factory: " + name);
        Factory<Asset>::RegisterClass<T>(name);
    }
};

#define REGISTER_ASSET(assetType) AssetCreator<assetType> assetType##Creator(#assetType);