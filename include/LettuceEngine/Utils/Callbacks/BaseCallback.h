#pragma once

typedef unsigned int CallbackID;

class BaseCallback {
    public:
        BaseCallback();
        virtual ~BaseCallback();

        virtual bool RemoveCallback(CallbackID id) = 0;
        virtual void RemoveAllCallbacks() = 0;
    protected:
        virtual bool ContainsID(CallbackID id) = 0;
        CallbackID GetNewId(bool increment = true);
        CallbackID _currentId;
};