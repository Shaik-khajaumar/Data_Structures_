#include <iostream>

class CDeque {
    int *arr {nullptr};
    int size {0};
    int capacity {0};
    int front {0};
    int rear {0};

    public:
    CDeque (int s) {
        arr = new int[s];
        capacity = s;
    } 

    bool isFull () {
        if (size == capacity) {
            return true;
        } 
        return false;
    }

    bool isEmpty () {
        if (size == 0) {
            return true;
        }
        return false;
    }

    bool insertFront (int val) {
        //check for full
        if (isFull ()) {
            return false;
        }

        if (front == 0 && rear == 0) {
            arr[0] = val;
            size++;
            return true;
        }

        if ((front + 1) % capacity != rear) {
            arr[(++front) % capacity] = val;
            size++;
            return true;
        }

        return false;

    }

    bool insertLast (int val) {
        //check for full
        if (isFull ()) {
            return false;
        }

        if (front == 0 && rear == 0) {
            arr[0] = val;
            size++;
            return true;
        }

        if (rear == 0) {
            rear = rear + capacity - 1;
            if (rear != front) {
                arr[rear] = val;
                size++;
                return true;
            }
        }
        else if ((rear - 1) != front) {
            arr[--rear] = val;
            size++;
            return true;
        }

        return false;
        
    }

    bool deleteFront () {
        if (isEmpty()) {
            return false;
        }

        if (front == 0) {
            front = capacity - 1;
            size--;
            return true;
        }
        else {
            front--;
            size--;
            return true;
        }
        return false;
    }

    bool deleteLast () {
        if (isEmpty()) {
            return false;
        }
        rear = (rear + 1)% capacity;
        size--;
        return true;
    }

    int getRear () {
        if (!isEmpty())
        return arr[front];
        return -1;
    }

    int getFront () {
        if (!isEmpty())
        return arr[rear];
        return -1;
    }
};

 
int main () {

    return 0;
}