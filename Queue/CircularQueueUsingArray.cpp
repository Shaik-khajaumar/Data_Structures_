#include <iostream>
class CircularQueue
{
private:
    private:
    int * arr; 
    int size;
    int front;
    int rear;

public:
    CircularQueue () {
        size = 7;
        arr = new int[7];
        front = 0;
        rear = 0;
    }

    CircularQueue(int _size) {
        size = _size;
        arr = new int[size];
        front = 0;
        rear = 0;
    }
    ~CircularQueue() {
        delete [] arr;
    }

    bool isempty () {
        if (front == rear) {
            return true;
        }
        return false;
    }

    void enqueue (int val) {
        if (((rear + 1) % size) == front) {
            std::cout<<"Queue is full\n";
        }
        else {
            rear = ((rear + 1) % size);
            arr[rear] = val;
        }

    }

    int dequeue () {
        int x = -1;
        if (isempty()) {
            std::cout<<"Queue is empty\n";
        }
        else {
            front = ((front + 1) % size);
            x = arr[front];
        }
        return x;
    }

    void display () {
        int temp = front;
        while (((temp + 1) % size) != (rear + 1) % size) {
            std::cout<<"data: "<<arr[temp + 1]<<" ";
            temp = ((temp + 1) % size);
        }
    }
};

int main() {
 
    int A[] = {1, 3, 5, 7, 9};

    std::cout<<sizeof(A)/sizeof(A[0]) + 1;
 
    CircularQueue cq(sizeof(A)/sizeof(A[0]) + 1);
 
    // Enqueue
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++){
        cq.enqueue(A[i]);
    }
 
    // Display
    cq.display();
    std::cout <<"\n";
 
    // Overflow
    cq.enqueue(10);
 
    // Dequeue
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++){
        cq.dequeue();
    }
 
    // Underflow
    cq.dequeue();
 
    return 0;
}