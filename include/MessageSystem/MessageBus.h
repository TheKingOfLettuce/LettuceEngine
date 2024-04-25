#pragma once
#include "MessageBase.h"
#include "MessageHandler.h"
#include <unordered_map>
#include <typeinfo>

class MessageBus {
    public:
        template <typename T, typename I>
        static void Subscribe(I* instance, void (I::*callback)(T*)) {
            // throws std::invalid_argument if instance or callback null
            CallbackHandler<T, I>* callHandler = new CallbackHandler<T, I>(instance, callback); 
            size_t messageType = typeid(T).hash_code();
            if (!HasMessageType(messageType))
                _eventMap[messageType] = new MessageHandler<T>();
               
            MessageHandlerBase* handler = _eventMap[messageType];
            MessageHandler<T>* actualHandler = dynamic_cast<MessageHandler<T>*>(handler);

            actualHandler->AddCallback(callHandler);
        }

        template <typename T, typename I>
        static void Unsubscribe(I* instance, void (I::*callback)(T*)) {
            size_t messageType = typeid(T).hash_code();
            if (!HasMessageType(messageType))
                return;

            // throws std::invalid_argument if instance or callback null
            CallbackHandler<T, I>* callHandler = new CallbackHandler<T, I>(instance, callback);
            MessageHandlerBase* handler = _eventMap[messageType];
            MessageHandler<T>* actualHandler = dynamic_cast<MessageHandler<T>*>(handler);

            actualHandler->RemoveCallback(callHandler);
        }

        template <typename T>
        static void UnsubscribeAll() {
            size_t messageType = typeid(T).hash_code();
            if (!HasMessageType(messageType))
                return;
            MessageHandlerBase* handler = _eventMap[messageType];
            _eventMap.erase(messageType);
            delete handler;
        }

        template <typename T>
        static void Publish(T* message) {
            size_t messageType = typeid(T).hash_code();
            if (!HasMessageType(messageType)) {
                delete message;
                return;
            }

            MessageHandlerBase* handler = _eventMap[messageType];
            MessageHandler<T>* actualHandler = dynamic_cast<MessageHandler<T>*>(handler);

            actualHandler->HandleCallback(message);

            delete message;
        }
        
    private:
        static std::unordered_map<size_t, MessageHandlerBase*> _eventMap;
        static bool HasMessageType(size_t key);
};