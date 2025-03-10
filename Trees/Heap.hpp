#include <iostream>
#include <vector>
#include <functional>

template<typename T>
class Heap {
    std::vector<T> v;
    std::function<bool(T, T)> compare;

    
    class comparator {
        public:
        bool operator ()(T a, T b) {
            return a > b;
        }
    };

    void heapify () {
        int size = v.size();
        for (int i = (size / 2) - 1; i >= 0; i--) {
            int cur_index = i;
            int left_index = (2 * i) + 1;

            while (left_index < size) {

                if (left_index + 1 < size) {
                    if (compare(v[left_index + 1], v[left_index])) {
                        left_index = left_index + 1;
                    }
                }

                if (compare(v[left_index], v[cur_index])) {
                    T temp = v[cur_index];
                    v[cur_index] = v[left_index];
                    v[left_index] = temp;
                    cur_index = left_index;
                    left_index = (2 * cur_index) + 1;
                }
                else {
                    break;
                }
            }
        }
    } 

    public:
    Heap () : compare(comparator()) {}

    Heap (std::vector<T> values) : v (values), compare (comparator()) {
        heapify();
    }

    Heap (std::function<bool(T, T)> user_compare) : compare(user_compare) {}

    Heap (std::vector<T> values, std::function<bool(T, T)> user_compare) : v (values), compare (user_compare) {
        heapify();
    }

    void add (T key) {
        v.push_back(key);
        int cur_index = v.size() - 1;
        int parent_index = (cur_index % 2 == 0)? (cur_index / 2) - 1 : (cur_index / 2);

        while (cur_index > 0 && compare (v[cur_index], v[parent_index])) {
            T temp = v[parent_index];
            v[parent_index] = v[cur_index];
            v[cur_index] = temp;
            cur_index = parent_index;
            parent_index = (cur_index % 2 == 0)? (cur_index / 2) - 1 : (cur_index / 2);
        }
    }

    T remove () {
        T removed_node = v[0];
        if (v.size() == 1) {
            v.pop_back();
            return removed_node;
        }

        v[0] = v[v.size() - 1];
        v.pop_back();
        int cur_index = 0;
        int left_index = (2 * cur_index) + 1;

        while (left_index < v.size()) {

            if (left_index + 1 < v.size()) {
                if (compare(v[left_index + 1], v[left_index])) {
                    left_index = left_index + 1;
                }
            }

            if (compare(v[left_index], v[cur_index])) {
                T temp = v[cur_index];
                v[cur_index] = v[left_index];
                v[left_index] = temp;
                cur_index = left_index;
                left_index = (2 * cur_index) + 1;
            }
            else {
                break;
            }
        }
        return removed_node;
    }
    void print() {
        for (auto& el : v) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
};