#pragma once
#include <functional>
#include <unordered_map>
#include "LettuceEngine/Utils/Callbacks/BaseCallback.h"

class Callback : public BaseCallback {
    public:
        Callback();
        ~Callback();

        CallbackID AddCallback(std::function<void(void)> callback);
        template <typename T>
        CallbackID AddCallback(void (T::* f)(), T* instance) {
            return AddCallback(std::bind(f, instance));
        }
        bool RemoveCallback(CallbackID id) override;
        void RemoveAllCallbacks() override;
        void Invoke();
    protected:
        std::unordered_map<CallbackID, std::function<void(void)>> _callbacks;

        bool ContainsID(CallbackID id) override;
};