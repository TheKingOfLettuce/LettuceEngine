#include "LettuceEngine/Components/Component.h"
#include <stdexcept>
#include <string>

using json = nlohmann::json;

Component::Component() {
    _enabled = false;
}

Component::~Component() {
    
}

void Component::Init(LettuceObject* obj) {
    if (obj == nullptr) {
        throw std::invalid_argument("Component was fed a null for LettuceObject owner");
    }
    _lettuce = obj;
}

void Component::Start() {}
void Component::Enabled() {}
void Component::Disabled() {}
void Component::Update(UpdateMessage* msg) {}
void Component::Render(RenderMessage* msg) {}

void Component::SetEnabled(bool flag) {
    if (_enabled == flag) return;
    _enabled = flag;

    _enabled ? Enabled() : Disabled();
}

bool Component::GetEnabled() const {
    return _enabled;
}

LettuceObject* Component::Lettuce() const {
    return _lettuce;
}

void Component::SaveToJson(json& j) {
    j["enabled"] = _enabled;
}

void Component::LoadFromJson(const json& data) {
    SetEnabled(data.at("enabled"));
}