#pragma once

#include <functional>
#include <unordered_map>
#include "Utils/Callbacks/BaseCallback.h"

template<typename Arg>
class CallbackWithArg : public BaseCallback {
    public:
        CallbackWithArg() {
            _callbacks = std::unordered_map<CallbackID, std::function<void(Arg)>>();
        }
        ~CallbackWithArg() {}
        
        CallbackID AddCallback(std::function<void(Arg)> callback) {
            CallbackID toReturn = GetNewId();
            _callbacks.emplace(toReturn, callback);

            return toReturn;
        }

        template<typename T>
        CallbackID AddCallback(void (T::* f)(Arg), T* instance) {
            return AddCallback(std::bind(f, instance, std::placeholders::_1));
        }

        bool RemoveCallback(CallbackID id) override {
            if (!ContainsID(id)) return false;

            _callbacks.erase(id);
            return true;
        }

        void RemoveAllCallbacks() override {
            _callbacks.clear();
        }

        void Invoke(Arg arg) {
            for (auto kv : _callbacks) {
                kv.second(arg);
            }
        }
    protected:
        std::unordered_map<CallbackID, std::function<void(Arg)>> _callbacks;

        bool ContainsID(CallbackID id) override {
            return _callbacks.find(id) != _callbacks.end();
        }
};