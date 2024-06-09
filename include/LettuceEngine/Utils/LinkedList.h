#pragma once
#include <stdexcept>
#include <string>

template <typename T>
struct Node {
    T Data;
    Node<T> *Next;
    Node<T> *Previous;
};

template <typename T>
class LinkedList {
    public:
        LinkedList() {
            _head = nullptr;
            _end = nullptr;
            _size = 0;
        }

        ~LinkedList() {
            if (_size == 0)
                return;
            Node<T>* current = _head;
            Node<T>* next = current->Next;
            while (current != nullptr) {
                delete current;
                current = next;
                if (current == nullptr)
                    break;
                next = current->Next;
            }

            _head = nullptr;
            _end = nullptr;
        }
        
        void Add(T item) {
            Node<T>* node = CreateNode(item);
            if (_end == nullptr) {
                _head = node;
            }
            else {
                _end->Next = node;
                node->Previous = _end;
            }
            _end = node;
            _end->Next = nullptr;
            _size++;
        }

        void Push(T item) {
            Node<T>* node = CreateNode(item);
            if (_head == nullptr) {
                _end = node;
            }
            else {
                node->Next = _head;
                _head->Previous = node;
            }
            _head = node;
            _size++;
        }

        bool Remove(T item) {
            if (_head == nullptr)
                return false;
            if (_head->Data == item) {
                Node<T>* node = _head;
                _head = _head->Next;
                if (_head != nullptr)
                    _head->Previous = nullptr;
                else 
                    _end = nullptr;
                _size--;
                delete node;
                return true;
            }
            else if (_size == 1)
                return false;
            else if (_end->Data == item) {
                Node<T>* node = _end;
                _end = _end->Previous;
                if (_end != nullptr)
                    _end->Next = nullptr;
                else
                    _head = nullptr;
                _size--;
                delete node;
                return true;
            }
            else if (_size == 2)
                return false;

            Node<T>* current = _head->Next;
            while (current != _end) {
                if (current->Data == item) {
                    Node<T>* node = current;
                    current->Previous->Next = current->Next;
                    current->Next->Previous = current->Previous;
                    _size--;
                    delete node;
                    return true;
                }
                current = current->Next;
            }

            return false;
        }

        T RemoveAt(int index) {
            if (index < 0 || index >= _size) {
                std::string errorString = "Index: " + std::to_string(index) + " is out of range of list size: " + std::to_string(_size);
                throw std::out_of_range(errorString);
            }

            if (_size == 1) {
                Node<T>* removeNode = _head;
                T toReturn = removeNode->Data;
                _head = nullptr;
                _end = nullptr;
                _size--;
                delete removeNode;
                return toReturn;
            }

            if (index == 0) {
                Node<T>* removeNode = _head;
                T toReturn = removeNode->Data;
                _head = _head->Next;
                _head->Previous = nullptr;
                _size--;
                if (_size == 1) {
                    _head->Next = nullptr;
                    _end = _head;
                }
                delete removeNode;
                return toReturn;
            }
            else if (index == _size-1) {
                Node<T>* removeNode = _end;
                T toReturn = removeNode->Data;
                _end = _end->Previous;
                _end->Next = nullptr;
                _size--;
                if (_size == 1) {
                    _end->Previous = nullptr;
                    _head = _end;
                }
                delete removeNode;
                return toReturn;
            }

            int count = 1;
            Node<T>* removeNode = _head->Next;
            while (count != index) {
                removeNode = removeNode->Next;
                count++;
            }
            removeNode->Previous->Next = removeNode->Next;
            removeNode->Next->Previous = removeNode->Previous;
            T toReturn = removeNode->Data;
            _size--;
            delete removeNode;
            return toReturn;

        }

        T Get(int index) {
            if (index < 0 || index >= _size) {
                std::string errorString = "Index: " + std::to_string(index) + " is out of range of list size: " + std::to_string(_size);
                throw std::out_of_range(errorString);
            }

            if (index == 0) {
                return _head->Data;
            }
            if (index-1 == _size) {
                return _end->Data;
            }

            Node<T>* current = _head->Next;
            int count = 1;
            while (count != index) {
                current = current->Next;
                count++;
            }

            return current->Data;
        }

        int GetIndex(T item) {
            int index = 0;
            Node<T>* current = _head;
            while (current != nullptr) {
                if (current->Data == item) {
                    return index;
                }
                index++;
                current = current->Next;
            }

            return -1;
        }

        void Clear() {
            while (_size != 0) {
                RemoveAt(0);
            }
        }

        int Size() {
            return _size;
        }

        T operator[](int index) {
            return Get(index);
        }

        Node<T>* GetHead() {
            return _head;
        }
    private:
        Node<T>* CreateNode(T item) {
            Node<T>* node = new Node<T>;
            node->Data = item;
            node->Next = nullptr;
            node->Previous = nullptr;

            return node;
        }
        
        int _size;
        Node<T>* _head;
        Node<T>* _end;
};