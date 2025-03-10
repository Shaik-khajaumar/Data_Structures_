#include <iostream>
#include <stack>
struct Stack {
    int _size {0};
    int _top {-1};
    int * _arr;

    int isempty () {
        if (_top == -1) {
            return true;
        }
        return false;
    }

    int size() {
        return _top + 1;
    }


    void push (int val) {
        if (_size == 0) {
            std::cout<<"Give stack some size\n";
            return;
        }
        if (_size - 1  == _top) {
            std::cout<<"Stack is full\n";
            return;
        }
        _arr[++_top] = val; 
    }

    void pop () {
        if (_top == -1) {
            std::cout<<"Stack is empty\n";
        }
        else {
            _top--;
        }
    }

    int& top () {
        if (isempty()) {
            std::cout<<"stack is empty\n";
        }
        else 
        return _arr[_top];
    }

    void traversal () {
        if (isempty()) {
            std::cout<<"stack is empty\n";
            return;
        }
        for( int i = _top; i >= 0; i-- ) {
            std::cout<<"Data: "<<_arr[i]<<" "<<i<<"\n";
        }
    }
};

int main () {
    struct Stack s;
    s._size = 7;
    s.pop();
    std::cout<<"Initially size: "<<s.size()<<"\n";
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout<<"After size: "<<s.size()<<"\n"<<"Top: "<<s.top()<<"\n";
    s.top() = 60;
    s.traversal();
    s.push(70);
    s.push(80);
    s.push(90);
    s.push(100);
    s.push(110);
    std::cout<<"Finally size: "<<s.size()<<"\n";
    s.traversal();







}