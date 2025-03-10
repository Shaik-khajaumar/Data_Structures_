#ifndef CIRCULARLINKEDLIST_HPP
#define CIRCULARLINKEDLIST_HPP
#include <iostream>
#include <vector>

template<typename T>
    class Node {
    T _data;
    Node<T>* _next {nullptr};

    public:
    Node (T data) : _data(data), _next(nullptr) {} //para cstr for Node

    T data() const { return _data; }
    void setData(T data) { _data = data; }

    Node<T>* next() const { return _next; }
    void setNext(Node<T>* next) { _next = next; }
    };

template<typename T>
class CircularLinkedList {

    Node<T>* _head {nullptr};
    Node<T>* _tail {nullptr};
    int _size {0};

    public:
    CircularLinkedList () : _head {nullptr} {}
    ~CircularLinkedList () {
        Node<T>* temp = _head;
        Node<T>* curr = temp;
        do {
        curr = temp;
        delete curr;
        temp = temp->next();
        } while (temp != _head);
    }

    bool empty () {
        if (_size == 0) {
            return true;
        }
        return false;
    }

    int size() {
        return _size;
    }

    void push_front (T data) {
        Node<T>* newNode = new Node<T>(data);

        if (_head == nullptr && _tail == nullptr) {
            _head = newNode;
            _tail = newNode;
            newNode->setNext(_head);
        }
        else {
            newNode->setNext(_head);
            _tail->setNext(newNode);
            _head = newNode;
        }
        _size++;
    }

    void push_back (T data) {
        Node<T>* newNode = new Node<T>(data);

        if (_head == nullptr && _tail == nullptr) {
            _head = newNode;
            _tail = newNode;
            newNode->setNext(_head);
        }
        else {
            _tail->setNext(newNode);
            _tail = newNode;
            newNode->setNext(_head);
        }
        _size++;
    }

    void insert_at_position (T data, int position) {

        if (empty() || position == 0) {
            return push_front(data);
        }

        if (position == _size) {
            return push_back(data);
        }

        if( position < 0 || position > _size) {
            std::cout<<"Invalid position\n";
            return;
        }
        Node<T>* newNode = new Node<T>(data);

        int t = 1;
        Node<T>* prev = _head;
        Node<T>* cur = _head->next();
        while (t != position) {
            t++;
            prev = cur;
            cur = cur->next();
        }

        prev->setNext(newNode);
        newNode->setNext(cur);
        _size++;
    }

    void pop_back() {
        if (empty()) {
            std::cout<<"List is empty\n";
            return;
        }

        if (_head->next() == _head) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            Node<T>* cur = _head;
            Node<T>* prev = nullptr;
            while (cur->next() != _head) {
                prev = cur;
                cur = cur->next();
            }
            prev->setNext(_head);
            _tail = prev;
            delete cur;
        }
        _size--;
    }

    void pop_front() {
        if (empty()) {
            std::cout<<"List is empty\n";
            return;
        }
        if (_head->next() == _head) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            Node<T>* cur = _head; 
            _head = _head->next();
            _tail->setNext(_head);
            delete cur;
        }
        _size--;
    }

    void delete_at_position (int position) {

        if (position < 0 || position >= size()) {
            std::cout<<"Invalid position\n";
            return;
        }

        if (position == 0) {
            return pop_front();
        }

        if (position == _size - 1) {
            return pop_back();
        }

        int t = 1;
        Node<T>* cur = _head->next();
        Node<T>* prev = _head;
        while (t != position) {
            t++;
            prev = cur;
            cur = cur->next();
        }
        prev->setNext(cur->next());
        delete cur;
        _size--;
    }

    std::vector<T> traversal () {
        if (!empty()) {
            std::vector<T> ans(_size);
            int i = 0;
            Node<T>* cur = _head;
            do {
                ans[i++] = cur->data();
                cur = cur->next();
            }while (cur != _head);
            return ans; 
        }
        std::cout<<"The list is empty\n";
        return std::vector<T> {};
    }
};

#endif // CIRCULARLINKEDLIST_HPP

