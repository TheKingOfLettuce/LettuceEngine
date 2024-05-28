#pragma once

#include "Utils/Factory.h"
#include "Component.h"

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

#define REGISTER_COMPONENT(derived_class) ComponentCreator<derived_class> derived_class##Creator(#derived_class);