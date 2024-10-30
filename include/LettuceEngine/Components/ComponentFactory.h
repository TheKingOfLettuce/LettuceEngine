#pragma once

#include "LettuceEngine/Utils/Factory.h"
#include "LettuceEngine/Components/Component.h"

template class Factory<Component>;

template <class T>
class ComponentCreator {
static_assert(std::is_base_of<Component, T>{},
"Provided type must be a Component");
public:
    explicit ComponentCreator(const std::string &name) {
        Log::Info("Registering component to factory: " + name);
        Factory<Component>::RegisterClass<T>(name);
    }
};

#define REGISTER_COMPONENT(componentType) ComponentCreator<componentType> componentType##Creator(#componentType);