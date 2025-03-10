#include <iostream>
#include <vector>
#include <queue>

template<typename T>
class N_ary_Node {
    T key;
    std::vector<N_ary_Node<T>*> children;

    public:
    N_ary_Node (T val) : key(val) {}
    
    void add_child (N_ary_Node<T>* child) {
        children.push_back(child);
    }

    ~N_ary_Node () {
        // delete all children nodes
        for (N_ary_Node<T>* temp : children) {
            delete temp;
        }
    }

    T Key() const {
        return key;
    }

    std::vector<N_ary_Node<T>*> Children () {
        return children;
    }
};

template<typename T>
std::vector<T> preorder(N_ary_Node<T>* root) {
    //if root exists first print it then check if children vector is empty or not
    //if children vector not empty then send each children but if it is empty then simple return
    if (root == nullptr) {
        return std::vector<T> {};
    }
    std::vector<T> v;
    v.push_back(root->Key());

    std::vector<N_ary_Node<T>*> children = root->Children();

    for (N_ary_Node<T>* child : children) {
        std::vector<T> next = preorder (child);
        v.insert(v.end(), next.begin(), next.end());
    }
    return v;
}

template<typename T>
std::vector<T> postorder (N_ary_Node<T>* root) {
    if (root == nullptr) {
        return std::vector<T> {};
    }
    std::vector<T> v;
    std::vector<N_ary_Node<T>*> children = root->Children();
    for (N_ary_Node<T>* child : children) {
        std::vector<T> next = postorder (child);
        v.insert(v.end(), next.begin(), next.end());
    }
    v.push_back(root->Key());
    return v;
}

template<typename T>
std::vector<std::vector<T>> levelorder (N_ary_Node<T>* root) {
    std::vector<std::vector<T>> v;
    if (root == nullptr) {
        return v;
    }
    v.push_back(std::vector<T>{root->Key()});
    std::queue<N_ary_Node<T>*> q;
    q.push(root);
    while (!q.empty ()) {
        int size = q.size();
        std::vector<T> temp_values;
        for (int i = 0; i < size; i++) {
            N_ary_Node<T>* temp = q.front();
            q.pop();
            std::vector<N_ary_Node<T>*> children = temp->Children();
            for (N_ary_Node<T>* child : children) {
                q.push(child);
                temp_values.push_back(child->Key());
            }
        }
        if (temp_values.size() > 0)
            v.push_back(temp_values);
    }

    return v;
}

int main () {

    N_ary_Node<int>* root = new N_ary_Node(50);
    N_ary_Node<int>* node1 = new N_ary_Node(25);
    N_ary_Node<int>* c1 = new N_ary_Node(12);
    N_ary_Node<int>* c2 = new N_ary_Node(14);
    N_ary_Node<int>* c3 = new N_ary_Node(8);
    N_ary_Node<int>* node2 = new N_ary_Node(25);
    N_ary_Node<int>* node3 = new N_ary_Node(23);
    N_ary_Node<int>* node4 = new N_ary_Node(45);
    N_ary_Node<int>* node5 = new N_ary_Node(17);
    N_ary_Node<int>* node6 = new N_ary_Node(15);

    

    root->add_child(node1);
    node1->add_child(c1);
    node1->add_child(c2);
    c2->add_child(c3);
    root->add_child(node2);
    root->add_child(node3);
    root->add_child(node4);
    node4->add_child(node5);
    node5->add_child(node6);

    auto preorder_values = preorder(root);
    for (auto& e : preorder_values) {
        std::cout<<e<<"\n";
    }

    auto postorder_values = postorder(root);
    for (auto& e : postorder_values) {
        std::cout<<e<<"\n";
    }

    std::cout<<"level order now: \n";
    std::vector<std::vector<int>> levelorder_values = levelorder(root);
    for (auto& e : levelorder_values) {
        for (auto& f : e)
            std::cout<<f<<"\n";
    }

    //delete the root also
    delete root;

    return 0;
}