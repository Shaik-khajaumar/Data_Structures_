//
//  CompleteBinaryTree.h
//  DataStructures
//
//  Created by Shaik on 26/01/25.
//

#ifndef CompleteBinaryTree_h
#define CompleteBinaryTree_h
#include "Binary_Tree_functions.h"
template <typename T>
class CompleteBinaryTree {
    std::vector<TreeNode<T>*> nodes;
    TreeNode<T>* root {nullptr};
    
    void deleteNode (TreeNode<T>* node) {
        if (node) {
            deleteNode (node->left);
            deleteNode (node->right);
            delete node;
        }
    }
    
    //This below is level order for just checking if remove is working correctly or not
    void print_level(TreeNode<T>* root, int level_no) {

        if (!root)
            return;
        if (level_no == 0) {
            // We are at the top of a subtree
            // So print the auxiliary root node
            printf("%d -> ", root->key);
        }
        else {
            print_level(root->left, level_no - 1);
            print_level(root->right, level_no - 1);
        }

    }
    void print_tree_level_order(TreeNode<T>* root) {
        if (!root)
            return;
        int height = get_height(root);
        for (int i=0; i<height; i++) {
            std::cout<<"Level: "<<i<<": ";
            print_level(root, i);
            printf("\n");
        }
        printf("\n\n-----Complete Level Order Traversal:-----\n");
        for (int i=0; i<height; i++) {
            print_level(root, i);
        }
        printf("\n");
    }
    
public:
    CompleteBinaryTree () {
        //To maintain indexex from 1 to n
        nodes.push_back(nullptr);
    }
    
    ~CompleteBinaryTree () {
        deleteNode(nodes[1]);
    }
    
    void add(T key) {
        int node_index = nodes.size();
        TreeNode<T>* newNode = new TreeNode(key);
        nodes.push_back(newNode);
        if (node_index == 1) {
            //Its the root node
            root = newNode;
            return;
        }
        
        int parent_index = (node_index) / 2;
        //need to check whether left child or right child
        if (nodes[parent_index]->left == nullptr) {
            //left child
            nodes[parent_index]->left = newNode;
        }
        else{
            //right child
            nodes[parent_index]->right = newNode;
        }
    }
    
    void remove (T key) {
        
        //special case root
        if (nodes[1]->key == key) {
            if (nodes[1]->left != nullptr) {
                nodes[1]->key = nodes[1]->left->key;
                nodes[1]->left->key = key;
            }
            else {
                root = nullptr;
                delete nodes[nodes.size() - 1];
                nodes.pop_back();
            }
        }
        
        for (int i = 2; i <= nodes.size(); i++) {
            
            if (nodes[i]->key == key) {
                int node_index = i;
                
                for (int j = node_index; j < nodes.size() - 1; j++) {
                    int parent_node_index = (j) / 2;
                    if (nodes[parent_node_index]->left->key == key) {
                        nodes[parent_node_index]->left->key = nodes[j + 1]->key;
                        nodes[parent_node_index]->right->key = key;
                    }
                    else {
                        nodes[parent_node_index]->right->key = nodes[j + 1]->key;
                        nodes[parent_node_index + 1]->left->key = key;
                    }
                    
                }
                
                int parent_node_index = (nodes.size() - 1) / 2;
                if (nodes[parent_node_index]->left->key == key) {
                    nodes[parent_node_index]->left = nullptr;
                }
                else {
                    nodes[parent_node_index]->right = nullptr;
                }
                delete nodes[nodes.size() - 1];
                nodes.pop_back();
                break;
            }
        }
        
        
    }
    
    int size() {
        return get_size(root);
    }
    
    std::vector<T> inorder () {
        std::vector<T> values;
        inorder_traversal(values, root);
        return values;
    }
    
    std::vector<T> postorder () {
        std::vector<T> values;
        postorder_traversal(values, root);
        return values;
    }
    
    std::vector<T> levelorder () {
        std::vector<T> values;
        levelorder_traversal(values, root);
        return values;
    }
    
    void level() {
        return print_tree_level_order(root);
    }
    
    std::vector<T> preorder () {
        std::vector<T> values;
        preorder_traversal(values, root);
        return values;
    }

};

#endif /* CompleteBinaryTree_h */
