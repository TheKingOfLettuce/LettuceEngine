#include "MessageSystem/MessageBus.h"

std::unordered_map<size_t, MessageHandlerBase*> MessageBus::_eventMap = std::unordered_map<size_t, MessageHandlerBase*>();

bool MessageBus::HasMessageType(size_t key) {
    return _eventMap.find(key) != _eventMap.end();
}