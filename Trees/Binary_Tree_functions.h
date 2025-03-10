//
//  Binary_Tree_functions.h
//  DataStructures
//
//  Created by Shaik on 25/01/25.
//

#ifndef Binary_Tree_functions_h
#define Binary_Tree_functions_h


#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include "TreeNode.h"
//This is header file containing all extra Binary Tree functions

template <typename T>
int get_height (TreeNode<T>* root) {
    if (root == nullptr) {
        return 0;
    }
    return std::max (get_height(root->left), get_height(root->right)) + 1;
}

template <typename T>
int get_size (TreeNode<T>* root) {
    if (root == nullptr) {
        return 0;
    }
    return get_size(root->left) + get_size(root->right) + 1;
}

template <typename T>
void preorder_traversal (std::vector<T>& values, TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    values.push_back (root->key);
    preorder_traversal (values, root->left);
    preorder_traversal (values, root->right);
}

template <typename T>
void inorder_traversal (std::vector<T>& values, TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    inorder_traversal (values, root->left);
    values.push_back (root->key);
    inorder_traversal (values, root->right);
    }

template <typename T>
void postorder_traversal (std::vector<T>& values, TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    postorder_traversal (values, root->left);
    postorder_traversal (values, root->right);
    values.push_back (root->key);
}

template <typename T>
void levelorder_traversal (std::vector<T>& values, TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }

    values.push_back(root->key);
    std::queue<TreeNode<T>*> q;
    q.push(root);
    
    while (!q.empty ()) {
        TreeNode<T>* temp = q.front();
        q.pop();
        if (temp->left != nullptr) {
            values.push_back(temp->left->key);
            q.push(temp->left);
        }
        
        if (temp->right != nullptr) {
            values.push_back(temp->right->key);
            q.push(temp->right);
        }
    }
}

template <typename T>
void left_view (std::vector<T>& values, TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    std::queue<std::pair<int, TreeNode<T>*>> q;
    q.push({0, root});
        
    int req_level = 0;
            
    while (!q.empty()) {
        int level = q.front().first;
        TreeNode<T>* temp = q.front().second;
        if (level == req_level) {
            values.push_back(temp->key);
            req_level++;
        }
        q.pop();
        if (temp->left != nullptr) {
            q.push({req_level, temp->left});
        }
        if (temp->right != nullptr) {
            q.push({req_level, temp->right});
        }
    }
}

template <typename T>
void right_view (std::vector<T>& values, TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    
    std::queue<std::pair<int, TreeNode<T>*>> q;
    q.push({0, root});
    int req_level = 0;
    
    while (!q.empty()) {
        int level = q.front().first;
        TreeNode<T>* temp = q.front().second;
        if (level == req_level) {
            values.push_back(temp->key);
            req_level++;
        }
        q.pop();
        if (temp->right != nullptr) {
            q.push({req_level, temp->right});
        }
        if (temp->left != nullptr) {
            q.push({req_level, temp->left});
        }
    }
}

template <typename T>
void bottom_view (std::vector<T>& values, TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }
    
    std::map<int, T> mp;
    std::queue<std::pair<int, TreeNode<T>*>> q;
    q.push({0, root});

    while (!q.empty()) {
        std::pair<int, TreeNode<T>*> t = q.front();
        q.pop();
        
        int level = t.first;
        TreeNode<T>* temp = t.second;

        if (mp.find(level) == mp.end()) {
            mp[level] = temp;
        }
        if (temp->left != nullptr) {
            q.push({level - 1, temp->left});
        }
        if (temp->right != nullptr) {
            q.push({level + 1, temp->right});
        }
    }

    for (std::pair<int, T> p : mp) {
        values.push_back(p.second);
    }

}

template <typename T>
void top_view(std::vector<T>& values, TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }

    std::map<int, T> mp;
    std::queue<std::pair<int, TreeNode<T>*>> q;

    q.push({0, root});

    while (!q.empty()) {
        std::pair<int, TreeNode<T>*> t = q.front();
        q.pop();

        int level = t.first;
        TreeNode<T>* temp = t.second;

        mp[level] = temp;

        if (temp->left != nullptr) {
            q.push({level - 1, temp->left});
        }
        if (temp->right != nullptr) {
            q.push({level + 1, temp->right});
        }
    }

    for (std::pair<int, T> p : mp) {
        values.push_back(p.second);
    }
}




#endif /* Binary_Tree_functions_h */
