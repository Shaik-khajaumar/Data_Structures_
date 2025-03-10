#include <iostream>
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


class Queue {
    Node * front {nullptr};
    Node * rear {nullptr};

    public:
    Queue () {
        front = nullptr;
        rear = nullptr;
    }

    ~Queue () {
        Node * temp = front;
        while (front != rear) {
            temp = front;
            front = front->next();
            delete temp;
        }
        delete rear;
    }

    bool isempty () {
        if (front == nullptr) {
            return true;
        }
        return false;
    }

    void push (int val) {
        Node * newNode = new Node (val);
        if (isempty ()) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->setNext(newNode);  
            rear = newNode;
            newNode->setNext(nullptr);
        }
    }

    void pop () {
        if (isempty ()) {
            std::cout<<"Queue is empty\n";
        }
        else {
            Node * temp = front;
            front = front->next();
            delete temp;
        }
    }

    int size () {
        int t {0};
        Node * temp = front;
        while (temp != nullptr) {
            t++;
            temp = temp->next();
        }
        return t;
    }

    void display () {
        if (isempty()) {
            std::cout<<"Queue is empty\n";
        }
        else {
        Node * temp = front;
        while (temp != nullptr) {
            std::cout<<"data: "<<temp->data()<<" ";
            temp = temp->next();
        }
        }
    }
};

int main () {

    Queue q;
    int A[] = {1, 3, 5, 7, 9};
 
 
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++){
        q.push(A[i]);
    }
 
    q.display();
 
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++){
        q.pop();
    }
    q.pop();

}