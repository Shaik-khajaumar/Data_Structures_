#include "LinkedList.hpp"
#include <stack>

class Stack {
    LinkedList list;

    public:
    Stack () {}
    ~Stack () {
        //no need I guess
    }

    bool empty () {
        return list.empty();
    }

    int size () {
        return list.size();
    }

    void push (int val) {
        list.push_front(val);
    }

    void pop () {
        list.pop_front();
    }

    int& top () {
        return list.getHead()->dataRef();
    }

    void traversal () {
        list.Traversal();
    }
};

int main () {
    Stack s;
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
    std::cout<<"-----------------------------\n";
    s.pop();
    s.pop();
    s.traversal();
}