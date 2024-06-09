#include "LettuceEngine/Utils/Callbacks/BaseCallback.h"

BaseCallback::BaseCallback() {
    _currentId = 0;
}

BaseCallback::~BaseCallback() {}

CallbackID BaseCallback::GetNewId(bool increment) {
    while (ContainsID(_currentId)) {
        _currentId++;
    }

    if (!increment)
        return _currentId;

    CallbackID toReturn = _currentId;
    _currentId++;
    return toReturn;
}