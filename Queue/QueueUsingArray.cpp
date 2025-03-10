#include <iostream>

class Queue
{
private:
    int * arr; 
    int size;
    int front;
    int rear;

public:
    Queue () {
        size = 7;
        arr = new int[7];
        front = 0;
        rear = -1;
    }

    Queue(int _size) {
        size = _size;
        arr = new int[size];
        front = 0;
        rear = -1;
    }

    ~Queue() {
        delete [] arr;
    }

    void push (int val) {
        if (rear == size - 1) {
            std::cout<<"Queue is full\n";
            return;
        }
        arr[++rear] = val;
    }

    void pop () {
        if (front > rear) {
            std::cout<<"Queue is empty\n";
            return;
        }
        front++;
    }

    int qsize () {
        return rear + 1;
    }

    bool isempty () {
        if (front > rear) {
            return true;
        }
        return false;
    }

    void display () {
        if (isempty ()) {
            std::cout<<"Queue is empty\n";
            return;
        }

        for (int i = front; i <= rear; i++) {
            std::cout<<"data: "<<arr[i]<<" ";
        }
    }
}; 

int main () {
    Queue q(5);
    q.display();
    std::cout<<"initially queue size: "<<q.qsize()<<"\n";
    q.pop();
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.display();
    q.pop();
    q.display();
    q.push(6);
    q.push(6);


    
}