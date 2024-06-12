#pragma once
#include <typeinfo>
#include <stdexcept>
#include <string>
#include <vector>

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
            _callbacks = std::vector<CallbackHandlerBase<T>*>();
            _messageType = typeid(T).hash_code();
        }

        ~MessageHandler() {
            for (size_t i = 0; i < _callbacks.size(); i++) {
                delete _callbacks[i];
            }
        }

        void AddCallback(CallbackHandlerBase<T>* callback) {
            if (callback == nullptr) {
                throw std::invalid_argument("MessageHandler was given a null callback");
            }
            _callbacks.push_back(callback);
        }

        void RemoveCallback(CallbackHandlerBase<T>* callback) {
            if (callback == nullptr) return;
            for (size_t i = 0; i < _callbacks.size(); i++) {
                CallbackHandlerBase<T>* current = _callbacks[i];
                if (*callback == current) {
                    delete _callbacks[i];
                    _callbacks.erase(_callbacks.begin() + i);
                    break;
                }
            }

            delete callback;
        }

        void HandleCallback(T* message) {
            for (size_t i = 0; i < _callbacks.size(); i++) {
                _callbacks[i]->HandleCallback(message);
            }
        }
    protected:
        std::vector<CallbackHandlerBase<T>*> _callbacks;
};