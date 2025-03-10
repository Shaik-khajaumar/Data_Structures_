//
//  BinaryTree.h
//  DataStructures
//
//  Created by Shaik on 25/01/25.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include "TreeNode.h"
#include <vector>
#include <queue>
#include <map>
#include <iostream>
//This is abstract class containging some pure virtual functions

template <typename T>
class BinaryTree {
public:
    
    virtual TreeNode<T>* add (T key) = 0;
    
    virtual TreeNode<T>* remove (T key) = 0;
    
    static int height (TreeNode<T>* root) {
        if (root == nullptr) {
            return 0;
        }
        return std::max (height(root->left), height(root->right)) + 1;
    }

    static int size (TreeNode<T>* root) {
        if (root == nullptr) {
            return 0;
        }
        return size(root->left) + size(root->right) + 1;
    }
    
    static void preorder (std::vector<T>& values, TreeNode<T>* root) {
        if (root == nullptr) {
            return;
        }
        values.push_back (root->key);
        inorder (values, root->left);
        inorder (values, root->right);
    }
    static std::vector<T> preorder_traversal (TreeNode<T>* root) {
        std::vector<T> values;
        preorder (values, root);
        return values;
    }
    
    static void inorder (std::vector<T>& values, TreeNode<T>* root) {
        if (root == nullptr) {
            return;
        }
        inorder (values, root->left);
        values.push_back (root->key);
        inorder (values, root->right);
    }
    static std::vector<T> inorder_traversal (TreeNode<T>* root) {
        std::vector<T> values;
        inorder (values, root);
        return values;
    }
    
    static void postorder (std::vector<T>& values, TreeNode<T>* root) {
        if (root == nullptr) {
            return;
        }
        inorder (values, root->left);
        inorder (values, root->right);
        values.push_back (root->key);
    }
    static std::vector<T> postorder_traversal (TreeNode<T>* root) {
        std::vector<T> values;
        postorder (values, root);
        return values;
    }

    static std::vector<T> levelorder_traversal (TreeNode<T>* root) {
        if (root == nullptr) {
            return std::vector<T> {};
        }
        
        std::vector<T> values;
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
        return values;
    }

    static std::vector<T> left_view (TreeNode<T>* root) {
        if (root == nullptr) {
            return std::vector<T> {};
        }

        std::queue<std::pair<int, TreeNode<T>*>> q;
        q.push({0, root});
            
        std::vector<T> values;
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
        return values;
    }

    static std::vector<T> right_view (TreeNode<T>* root) {
        if (root == nullptr) {
            return std::vector<T> {};
        }

        std::queue<std::pair<int, TreeNode<T>*>> q;
        q.push({0, root});
        std::vector<T> values;
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
        return values;
    }

    static std::vector<T> bottom_view (TreeNode<T>* root) {
        if (root == nullptr) {
            return std::vector<T> {};
        }
        
        std::vector<T> values;
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

        return values;
    }

    static std::vector<T> top_view(TreeNode<T>* root) {
        if (root == nullptr) {
            return std::vector<int> {};
        }
        
        std::vector<T> values;
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

        return values;
    }

};

#endif /* BinaryTree_h */
