#pragma once

#include "Utils/Factory.h"
#include "Assets/Asset.h"

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

#define REGISTER_ASSET(derived_class) AssetCreator<derived_class> derived_class##Creator(#derived_class);