#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>
#include <vector>
/*
    PUT CONST AFTER ALL MEMBER FUNCTIONS OR ELSE CANNOT USE
    const LinkedList as parameter
*/
template<typename T>
class Node {
        T _data;
        Node<T> * _next {nullptr};

        public:
        Node (T data) : _data(data), _next(nullptr) {} //para cstr for Node

        T data() const { return _data; }
        void setData(T data) { _data = data; }

        Node<T> * next() const { return _next; }
        void setNext(Node<T> * next) { _next = next; }
    };

template<typename T>
class LinkedList {

    Node<T>* head {nullptr};
    Node<T>* tail {nullptr};
    int _size {0};

    public:
    LinkedList () : head(nullptr), tail(nullptr), _size(0) {} //default cstr for LinkedList

    ~LinkedList () { // Need to delete all dynamically allocated Nodes
        Node<T>* cur = nullptr;
        while (head != nullptr) {
        cur = head;
        head = head->next();
        delete cur;
        }
    }

    bool empty() {
        if (_size == 0) {
            return true;
        }
        return false;
    }

    int size () {
        return _size;
    }

    /*
        Insertion
    */
    void push_front (T data){
        if (_size == 0) {
            Node<T> * newNode = new Node<T>(data);
            head = newNode;
            tail = newNode;
            _size++;
        }
        else {
            Node<T> * newNode = new Node<T>(data);
            newNode->setNext(head);
            head = newNode;
            _size++;
        }
    }

    void push_back (T data)
    {
        if (_size == 0) {
            Node<T> * newNode = new Node<T>(data);
            head = newNode;
            tail = newNode;
            _size++;
        }
        else {
            Node<T> * newNode = new Node<T>(data);
            tail->setNext(newNode);
            tail = newNode;
            _size++;
        }
    }

    void insert_at_position (T data, int position) {

        if (position < 0 || position > _size) {
            std::cout<<"Invalid Position\n";
            return;
        }

        // If the list is empty or if position is 0th
        if (_size == 0 || position == 0) {
            push_front(data);
        }
        else if (position == _size) {
            push_back(data);
        }
        else {

            Node<T> * newNode = new Node<T>(data);

            int t = 1;
            Node<T> * prev = head;
            Node<T> * cur = head->next();         //Redundant Code traversal(insert)
            
            while (t != position) {
                t++;
                prev = cur;
                cur = cur->next();
            }

            prev->setNext(newNode);
            newNode->setNext(cur);
            _size++;
        }
    }

    /*
        Deletion
    */
   void pop_front () {
        if (empty()) {
            std::cout<<"list is empty\n";
            return;
        }
        if (!empty() && head == tail) {
            delete head;
            head = tail = nullptr;
            _size--;
            return;
        }
        if (!empty()) {
            Node<T> * temp = head;
            head = head->next();
            delete temp;
            _size--;
            return;
        }
   }

   void pop_back () 
    {
        if (empty()) {
            std::cout<<"list is empty\n";
            return;
        }

        if (!empty() && head == tail) {
            delete head;
            head = tail = nullptr;
            _size--;
            return;
        }
        if (!empty()) {
            delete_at_position(_size - 1);
        }
    }

       void delete_at_position (int position) {
        
        if (empty()) {
            std::cout<<"list is empty\n";
            return;
        }

        if (position < 0 || position >= _size) {
            std::cout<<"Invalid Position\n";
            return;
        }

        if (position == 0) {
            return pop_front();
        }

        if (!empty()) {
            int t = 1;
            Node<T> * prev = head;
            Node<T> * cur = head->next();

            while (t != position) {
                t++;
                prev = cur;
                cur = cur->next();
            }
            prev->setNext(cur->next());
            if (cur == tail) {
                tail = prev;
            }
            delete cur;
            _size--;
            return;
        }
   }

    /*
        Traversing the linkedlist
    */
    std::vector<T> traversal () {
        if (_size > 0) {
        std::vector<T> v(_size);
        Node<T> * cur = head;
        int i = 0;
        while (cur != nullptr) {               
            v[i++] = cur->data();
            cur = cur->next();
        }
        return v;
        }
        std::cout<<"The list is empty\n";
        return std::vector<T> {};
    }

    Node<T> * getHead() const { return head; }

    void setHead(Node<T> * head_) { head = head_; }
};  

#endif // LINKEDLIST_HPP
