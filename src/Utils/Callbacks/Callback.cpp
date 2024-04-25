#include "Utils/Callbacks/Callback.h"

Callback::Callback() {
    _callbacks = std::unordered_map<CallbackID, std::function<void(void)>>();
}

Callback::~Callback() {}

CallbackID Callback::AddCallback(std::function<void(void)> callback) {
    CallbackID toReturn = GetNewId();
    _callbacks.emplace(toReturn, callback);

    return toReturn;
}

bool Callback::RemoveCallback(CallbackID id) {
    if (!ContainsID(id)) return false;

    _callbacks.erase(id);
    return true;
}

void Callback::RemoveAllCallbacks() {
    _callbacks.clear();
}

void Callback::Invoke() {
    for (auto kv : _callbacks) {
        kv.second();
    }
}

bool Callback::ContainsID(CallbackID id) {
    return _callbacks.find(id) != _callbacks.end();
}