#include "LettuceObject.h"
#include "Logging/Log.h"
#include "Components/ComponentFactory.h"

using json = nlohmann::json;
using LettuceEngine::Math::Vector2;

LettuceObject::LettuceObject() {
    _position = Vector2(0.0f, 0.0f);
    _rotation = 0;
    _scale = Vector2(1.0f, 1.0f);
    _enabled = true;

    _components = new std::unordered_map<size_t, LinkedList<Component*>*>();
    _children = new std::vector<LettuceObject*>();
    _positionChangeCallback = new CallbackWithArg<bool>();
}

LettuceObject::~LettuceObject() {
    for (auto kv: *_components) {
        size_t componentType = kv.first;
        LinkedList<Component*>* componentList = _components->at(componentType);
        while (componentList->Size() != 0) {
            delete componentList->RemoveAt(0);
        }

        delete componentList;
    }

    while (!_children->empty()) {
        delete _children->operator[](0);
        _children->erase(_children->begin());
    }
    delete _components;
    delete _children;
}

void LettuceObject::AddComponent(Component* component, bool startEnabled) {
    if (component == nullptr) {
        throw std::invalid_argument("LettuceObject was fed a null component");
    }

    size_t componentType = typeid(*component).hash_code();
    if (_components->find(componentType) == _components->end()) {
        _components->emplace(componentType, new LinkedList<Component*>());
    }
    _components->at(componentType)->Add(component);
    component->Init(this);
    component->Start();
    component->SetEnabled(startEnabled);
}

bool LettuceObject::RemoveComponent(Component* component) {
    size_t toRemove = typeid(component).hash_code();
    if (_components->find(toRemove) == _components->end()) return false;
    LinkedList<Component*>* componentList = _components->at(toRemove);
    if (componentList->Remove(component)) {
        if (componentList->Size() == 0) {
            delete componentList;
            _components->erase(toRemove);
        }
        return true;
    }
    return false;
}

void LettuceObject::SetEnable(bool flag) {
    if (_enabled == flag) return;
    _enabled = flag;
    for (auto kv: *_components) {
        size_t componentType = kv.first;
        LinkedList<Component*>* componentList = _components->at(componentType);
        for (int i = 0; i < componentList->Size(); i++) {
            componentList->Get(i)->SetEnabled(flag);
        }
    }

    for (LettuceObject* child : *_children) {
        child->SetEnable(flag);
    }
}

void LettuceObject::Update(UpdateMessage* msg) {
    for (auto const& pair : *_components) {
        LinkedList<Component*>* componentList = pair.second;
        for (int i = 0; i < componentList->Size(); i++) {
            Component* c = componentList->Get(i);
            if (!c->GetEnabled()) continue;
            c->Update(msg);
        }
    }

    for (LettuceObject* child : *_children) {
        if (!child->Enabled()) continue;
        child->Update(msg);
    }
}

void LettuceObject::Render(RenderMessage* msg) {
    for (auto const& pair : *_components) {
        LinkedList<Component*>* componentList = pair.second;
        for (int i = 0; i < componentList->Size(); i++) {
            Component* c = componentList->Get(i);
            if (!c->GetEnabled()) continue;
            c->Render(msg);
        }
    }

    for (LettuceObject* child : *_children) {
        if (!child->Enabled()) continue;
        child->Render(msg);
    }
}

void LettuceObject::AddChild(LettuceObject* child) {
    if (child == nullptr) {
        throw std::invalid_argument("LettuceObject was fed a null child");
    }

    _children->push_back(child);
}

bool LettuceObject::RemoveChild(LettuceObject* child) {
    for (int i = 0; i < _children->size(); i++) {
        if (_children->operator[](i) == child) {
            _children->erase(_children->begin()+i);
            return true;
        }
    }

    return false;
}

LettuceObject* LettuceObject::RemoveChildAt(int index) {
    LettuceObject* toReturn = GetChildAt(index);
    if (toReturn != nullptr)
        _children->erase(_children->begin() + index);
    return toReturn;
}

LettuceObject* LettuceObject::GetChildAt(int index) {
    if (index < 0 || index >= _children->size()) {
        throw std::out_of_range("index is out of range");
    }

    return _children->operator[](index);
}

int LettuceObject::GetChildIndex(LettuceObject* child) {
    for (int i = 0; i < _children->size(); i++) {
        if (_children->operator[](i) == child) {
            return i;
        }
    }

    return -1;
}

Vector2 LettuceObject::Position() const {
    return _position;
}

void LettuceObject::SetPosition(Vector2 newPos) {
    _positionChangeCallback->Invoke(false);

    Vector2 diff = newPos - _position;
    _position = newPos;

    _positionChangeCallback->Invoke(true);

    for (LettuceObject* child : *_children) {
        child->SetPosition(child->Position() + diff);
    }
}

float const LettuceObject::Rotation() {
    return _rotation;
}

Vector2 LettuceObject::Scale() const {
    return _scale;
}

bool const LettuceObject::Enabled() {
    return _enabled;
}

size_t const LettuceObject::NumChildren() {
    return _children->size();
}

LettuceObjectData LettuceObject::SaveToData() {
    std::vector<ComponentPair> componentData = std::vector<ComponentPair>();

    for (auto const& pair : *_components) {
        LinkedList<Component*>* componentList = pair.second;
        for (int i = 0; i < componentList->Size(); i++) {
            ComponentPair pair = ComponentPair();
            Component* c = componentList->Get(i);
            const std::string typeName = Factory<Component>::GetSaveName(typeid(*c).hash_code());
            if (typeName.empty())  {
                Log::Info("Received an empty component type when saving LettuceObject");
                continue;
            }
            pair.TypeName = typeName;
            json j;
            c->SaveToJson(j);
            pair.ComponentData = j;
            componentData.push_back(pair);
        }
    }
    std::vector<LettuceObjectData> childrenData = std::vector<LettuceObjectData>();
    for (LettuceObject* child : *_children) {
        childrenData.push_back(child->SaveToData());
    }
    LettuceObjectData data = LettuceObjectData();
    data.Enabled = _enabled;
    data.Position = _position;
    data.ComponentData = componentData;
    data.ChildrenData = childrenData;

    return data;
}

CallbackWithArg<bool>* LettuceObject::OnPositionChanged() {
    return _positionChangeCallback;
}

void LettuceObject::LoadFromData(LettuceObjectData data) {
    SetEnable(data.Enabled);
    SetPosition(data.Position);

    for (auto const& pair : data.ComponentData) {
        Component* c = Factory<Component>::Create(pair.TypeName);
        if (c == nullptr) {
            Log::Warning("Attempted to load component [" + pair.TypeName + "] but was not created");
            continue;
        }
        c->LoadFromJson(pair.ComponentData);
        AddComponent(c, c->GetEnabled());
    }

    for(LettuceObjectData childData : data.ChildrenData) {
        LettuceObject* child = new LettuceObject();
        AddChild(child);
        child->LoadFromData(childData);
    }
}

void to_json(json& j, const ComponentPair& data) {
    j = json{
        {"typeName", data.TypeName},
        {"data", data.ComponentData}
    };
}

void from_json(const json& j, ComponentPair& data) {
    j.at("typeName").get_to(data.TypeName);
    j.at("data").get_to(data.ComponentData);
}

void to_json(json& j, const LettuceObjectData& data) {
    j = json{
        {"enabled", data.Enabled},
        {"position", data.Position},
        {"componentData", data.ComponentData},
        {"childData", data.ChildrenData}
    };
}

void from_json(const json& j, LettuceObjectData& data) {
    j.at("enabled").get_to(data.Enabled);
    j.at("position").get_to(data.Position);
    j.at("componentData").get_to(data.ComponentData);
    j.at("childData").get_to(data.ChildrenData);
}