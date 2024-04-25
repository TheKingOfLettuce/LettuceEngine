#pragma once
#include <typeinfo>
#include <stdexcept>
#include <string>
#include "Utils/LinkedList.h"

template <typename T>
class CallbackHandlerBase {
    public:
        virtual ~CallbackHandlerBase() = default;

        virtual void HandleCallback(T* message) = 0;
        virtual bool operator == (CallbackHandlerBase<T>* other) const = 0;
        virtual bool operator != (CallbackHandlerBase<T>* other) const = 0;
};

template <typename T, typename I>
class CallbackHandler : public CallbackHandlerBase<T> {
    public:
        CallbackHandler(I* instance, void (I::*callback)(T*)) : _instance(instance), _callback(callback) {
            if (_instance == nullptr) {
                throw std::invalid_argument("CallbackHandler was fed a null instance.");
            }
            if (_callback == nullptr) {
                throw std::invalid_argument("CallbackHandler was fed a null callback.");
            }
        }
        ~CallbackHandler() {}

        void HandleCallback(T* message) override {
            (_instance->*_callback)(message);
        }

        bool operator == (CallbackHandlerBase<T>* other) const override {
            CallbackHandler* otherEventCallback = dynamic_cast<CallbackHandler*>(other);
            if (otherEventCallback == nullptr)
                return false;
    
            return 	this->_callback == otherEventCallback->_callback && 
                this->_instance == otherEventCallback->_instance;
        }

        bool operator == (CallbackHandler<T, I> other) const {
            return this->_callback == other._callback && this->_instance == other._instance;
        }

        bool operator != (CallbackHandlerBase<T>* other) const override {
            return !operator==(other);
        }

        bool operator != (CallbackHandler<T, I> other) const {
            return !operator==(other);
        }

    private:
        void (I::*_callback)(T*);
        I* _instance;
};

class MessageHandlerBase {
    public:
        virtual ~MessageHandlerBase() = default;
        size_t GetMessageType() {
            return _messageType;
        }
    protected:
        size_t _messageType;
};

template <typename T>
class MessageHandler : public MessageHandlerBase {
    public:
        MessageHandler() {
            _callbacks = new LinkedList<CallbackHandlerBase<T>*>();
            _messageType = typeid(T).hash_code();
        }

        ~MessageHandler() {
            while(_callbacks->Size() != 0) {
                delete _callbacks->RemoveAt(0);
            }
            delete _callbacks;
        }

        void AddCallback(CallbackHandlerBase<T>* callback) {
            if (callback == nullptr) {
                throw std::invalid_argument("MessageHandler was given a null callback");
            }
            _callbacks->Add(callback);
        }

        void RemoveCallback(CallbackHandlerBase<T>* callback) {
            if (callback == nullptr) return;
            Node<CallbackHandlerBase<T>*>* curent = _callbacks->GetHead();
            int count = 0;
            while (curent != nullptr) {
                if (*callback == curent->Data) {
                    delete _callbacks->RemoveAt(count);
                    break;
                }
                count++;
                curent = curent->Next;
            }

            delete callback;
        }

        void HandleCallback(T* message) {
            Node<CallbackHandlerBase<T>*>* current = _callbacks->GetHead();
            while (current != nullptr) {
                current->Data->HandleCallback(message);
                current = current->Next;
            }
        }
    protected:
        LinkedList<CallbackHandlerBase<T>*>* _callbacks;
};