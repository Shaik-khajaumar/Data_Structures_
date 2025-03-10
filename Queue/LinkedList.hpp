#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>
#include <forward_list>
/*
    PUT CONST AFTER ALL MEMBER FUNCTIONS OR ELSE CANNOT USE
    const LinkedList as parameter
*/
    class Node {
        int _data;
        Node * _next {nullptr};

        public:
        Node (int data) : _data(data), _next(nullptr) {} //para cstr for Node

        int data() const { return _data; }
        void setData(int data) { _data = data; }

        Node * next() const { return _next; }
        void setNext(Node * next) { _next = next; }
    };

class LinkedList {

    Node * head {nullptr};

    bool checkPosition(int position) {
        if (position < 0 || position > size()) {
            std::cout<<"Invalid Position\n";
            return false;
        }
        return true;
    }

    public:
    LinkedList () : head(nullptr) {} //default cstr for LinkedList

    ~LinkedList () { // Need to delete all dynamically allocated Nodes
       while (head != nullptr) { //REDUNDANT CODE 1
        Node * temp = head;
        head = head->next();
        delete temp;
        }
    }

    bool empty() {
        if (head == nullptr) {
            std::cout<<"List is empty\n";
            return true;
        }
        return false;
    }
    /*
        Insertion
    */
    void push_front (int data){

        Node * newNode = new Node(data);
        newNode->setNext(head);
        head = newNode;
    }

    void InsertAtPosition (int data, int position) {

        if (!empty() && checkPosition(position)) {
        Node * newNode = new Node(data);

        int t = 0;
        Node * temp = head;         //Redundant Code traversal(insert)
        Node * prev = head;
        while (temp != nullptr) {
            t++;
            if (t == position) {
                prev->setNext(newNode);
                newNode->setNext(temp);
                return;
            }
            prev = temp;
            temp = temp->next();
        }
    }
    }

    void psuh_back (int data)
    {
        InsertAtPosition(data, size());
    }

    /*
        Deletion
    */
   void pop_front ()
   {
    if (!empty()) {
    Node * temp = head;
    head = head->next();
    delete temp;
    }
    }

   void DeleteAtPosition (int position) 
   {
    if (!empty() && checkPosition(position)) {
    int t = 0;
        Node * temp = head;         //Redundant Code can be Traversal(delete)
        Node * prev = head;
        while (temp != nullptr) {
            t++;
            if(t == position) {
                prev->setNext(temp->next());
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next();
        }
    }
   }

   void pop_back () 
    {
        DeleteAtPosition(size());
    }

    /*
        Traversing the linkedlist
    */
    void Traversal () 
    {
    if(!empty()) {
    Node * temp = head;         //REDUNDANT CODE traversal can be traversal()
    while (temp != nullptr) {               
        std::cout<<"Data: "<<temp->data()<<"\n";
        temp = temp->next();
    }
    }
    }

    /*
        size of the linkedlist
    */
    std::size_t size () 
    {
    if(!empty()) {
    std::size_t _size {0};
    Node * temp = head;         //REDUNDANT  can be traversal(sizeparameter)
    while (temp != nullptr) {
        _size++;
        temp = temp->next();
    }
    return _size++;
    }
    }

    Node * getHead() const { return head; }

    void setHead(Node * head_) { head = head_; }
};  

#endif // LINKEDLIST_HPP
