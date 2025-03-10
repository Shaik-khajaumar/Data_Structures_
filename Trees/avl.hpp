
//
//  avl.hpp
//  keyStructures
//
//  Created by Shaik on 18/01/25.
//

#ifndef avl_h
#define avl_h

#include "Binary_Tree_functions.h"
template <typename T>
class avl {
    std::map<TreeNode<T>*, int> mp;
    TreeNode<T>* root {nullptr};
    std::function<bool(T,T)> compare;
    std::function<bool(T,T)> compare_equal;
    
    int get_balance_factor(TreeNode<T>* root) {
        // checking balance factor now

        int left_ht = 0, right_ht = 0;
        if (root->left != nullptr) {
            left_ht = mp[root->left] + 1;
        }
        if (root->right != nullptr) {
            right_ht = mp[root->right] + 1;
        }

        int balance_factor = left_ht - right_ht;
        return balance_factor;
    }
    
    TreeNode<T>* rr_rotation (TreeNode<T>* root) {
        //total left from root

        TreeNode<T>* root_right = root->right;
        TreeNode<T>* root_right_left = root_right->left;
        root->right = root_right_left;
        root_right->left = root;

        //update heights of root, then root_right
        mp[root] = 0;
        if (root->left != nullptr) {
            mp[root] = std::max(mp[root->left] + 1, mp[root]);
        }
        if (root->right != nullptr) {
            mp[root] = std::max(mp[root->right] + 1, mp[root]);
        }

        mp[root_right] = 0;
        if (root_right->left != nullptr) {
            mp[root_right] = std::max(mp[root_right->left] + 1, mp[root_right]);
        }
        if (root_right->right != nullptr) {
            mp[root_right] = std::max(mp[root_right->right] + 1, mp[root_right]);
        }
        
        return root_right;
    }

    TreeNode<T>* ll_rotation (TreeNode<T>* root) {
        //total right from root

        TreeNode<T>* root_left = root->left;
        TreeNode<T>* root_left_right = root_left->right;
        root->left = root_left_right;
        root_left->right = root;

        //update heights of root, then root_left
        mp[root] = 0;
        if (root->left != nullptr) {
            mp[root] = std::max(mp[root->left] + 1, mp[root]);
        }
        if (root->right != nullptr) {
            mp[root] = std::max(mp[root->right] + 1, mp[root]);
        }

        mp[root_left] = 0;
        if (root_left->left != nullptr) {
            mp[root_left] = std::max(mp[root_left->left] + 1, mp[root_left]);
        }
        if (root_left->right != nullptr) {
            mp[root_left] = std::max(mp[root_left->right] + 1, mp[root_left]);
        }

        return root_left;
    }
    
    TreeNode<T>* insert (TreeNode<T>* root, T key)  {
        
        if (root == nullptr) {
            mp[root] = 0;
            return new TreeNode(key);
        }
        if (compare_equal(root->key, key)) {
            return root;
        }
        /*
            first insert at appropriate place

            if unbalanced perform rotation and update height

            if correct only then just update heights
            
            return
        */

        if (compare(key, root->key)) {
            root->left = insert (root->left, key);
        }
        else {
            root->right = insert (root->right, key);
        }

        //update heights
        if (root->left != nullptr) {
            mp[root] = std::max(mp[root->left] + 1, mp[root]);
        }
        if (root->right != nullptr) {
            mp[root] = std::max(mp[root->right] + 1, mp[root]);
        }

        // checking balance factor now

        int balance_factor = get_balance_factor(root);

        if (balance_factor < -1 || balance_factor > 1) {
            if (balance_factor > 0) {
                //left tree is big
                int sub_root_balance_factor = get_balance_factor(root->left);
                if (sub_root_balance_factor < 0) {
                    //right tree is big, this is LR
                    //lr means sub_root is rotated to left and root is rotated to right
                    //sub_root is root->left
                    root->left = rr_rotation(root->left);
                    root = ll_rotation(root);
                }
                else {
                    //left tree is big, this is LL
                    root = ll_rotation(root);
                }
            }
            else {
                //right tree is big
                int sub_root_balance_factor = get_balance_factor(root->right);
                if (sub_root_balance_factor > 0) {
                    //left tree is big, this is RL
                    //rl means sub_root is roatated to right and root is rotated to left
                    root->right = ll_rotation(root->right);
                    root = rr_rotation(root);
                }
                else {
                    //right tree is big, this is RR
                    root = rr_rotation(root);
                }
            }
        }

        return root;
    }
    
    TreeNode<T>* remove_node (TreeNode<T>* root, T key) {
            
        if (root == nullptr) {
            return nullptr;
        }


        if (compare_equal (root->key, key)) {
            //get inorder predessor or successor from that node only not from actual root
            if (root->left == nullptr && root->right == nullptr) {
                //its a leaf node
                mp.erase(root);
                delete root;
                //no need to check balance factor as we are removing the leaf node
                root = nullptr;
                return root;
                
            }
            else if (root->left != nullptr && root->right == nullptr) {
                mp.erase(root);
                TreeNode<T>* left_node = root->left;
                delete root;
                return left_node;
            }
            else if (root->right != nullptr && root->left == nullptr) {
                mp.erase(root);
                TreeNode<T>* right_node = root->right;
                delete root;
                return right_node;
            }
            else {
                TreeNode<T>* pre = get_pre(root);
                T new_value = pre->key;
                root->left = remove_node(root->left, pre->key);
                mp[root] = 0;
                root->key = new_value;
            }
        }
        else if (compare (key, root->key)) {
            root->left = remove_node (root->left, key);
        }
        else {
            root->right = remove_node (root->right, key);
        }
        
        //important step, for examples if a node now becomes leaf then its height in update heights wont change as both conditions evaluate to false so doing this is important
        mp[root] = 0;

        //update heights
        if (root->left != nullptr) {
            mp[root] = std::max(mp[root->left] + 1, mp[root]);
        }
        if (root->right != nullptr) {
            mp[root] = std::max(mp[root->right] + 1, mp[root]);
        }

        // checking balance factor now

        int balance_factor = get_balance_factor(root);
        if (balance_factor < -1 || balance_factor > 1) {
            if (balance_factor < 0) {
                //right tree is big and causing imbalance
                int sub_root_balance_factor = get_balance_factor(root->right);
                if (sub_root_balance_factor < 0) {
                    //right sub tree is big and causing imbalance, RR means total left
                    root = rr_rotation(root);
                }
                else {
                    //left sub tree is big, this is RL
                    root->right = ll_rotation(root->right);
                    root = rr_rotation(root);
                }
            }
            else {
                //left tree is big and causing imbalance
                int sub_root_balance_factor = get_balance_factor(root->left);
                if (sub_root_balance_factor > 0) {
                    //left sub tree is big, this is LL means total right
                    root = ll_rotation(root);
                }
                else {
                    //right sub tree is big, this is LR
                    root->left = rr_rotation(root->left);
                    root = ll_rotation(root);
                }
            }
        }
        return root;
    }
    
    void deleteNode (TreeNode<T>* node) {
        if (node) {
            deleteNode (node->left);
            deleteNode (node->right);
            delete node;
        }
    }
    
    public:
    avl () : root (nullptr) {
        compare = [&] (T a, T b) -> bool {
            return a < b;
        };
        compare_equal = [&] (T a, T b) -> bool {
            return a == b;
        };
    }
    
    avl (std::function<bool(T,T)> user_compare, std::function<bool(T,T)> user_compare_equal) : root (nullptr), compare(user_compare), compare_equal(user_compare_equal) {}
    ~avl () {
        deleteNode(root);
    }
    
    void add(T key) {
        root = insert(root, key);
    }
    
    void remove (T key)  {
        root = remove_node (root, key);
    }

    TreeNode<T>* get_pre (TreeNode<T>* root) {
        //pre means go to left subtree and find right most node and return
        root = root->left;
        while (root && root->right != nullptr) {
            root = root->right;
        }
        return root;
    }

    TreeNode<T>* get_suc (TreeNode<T>* root) {
        //sucessor means go to right subtree and find left most node and return
        root = root->right;
        while (root && root->left != nullptr) {
            root = root->left;
        }
        return root;
    }
    
    std::vector<T> inorder() {
        std::vector<T> values;
        inorder_traversal (values, root);
        return values;
    }
    
    std::vector<T> postorder() {
        std::vector<T> values;
        postorder_traversal (values, root);
        return values;
    }

    std::vector<T> preorder() {
        std::vector<T> values;
        inorder_traversal(values, root);
        return values;
    }
    
    std::vector<T> levelorder() {
        std::vector<T> values;
        levelorder_traversal(values, root);
        return values;
    }
    
    std::vector<T> topview() {
        std::vector<T> values;
        top_view (values, root);
        return values;
    }
    
    std::vector<T> bottomview() {
        std::vector<T> values;
        bottom_view (values, root);
        return values;
    }
    
    std::vector<T> rightview() {
        std::vector<T> values;
        right_view (values, root);
        return values;
    }
    
    std::vector<T> leftview() {
        std::vector<T> values;
        left_view (values, root);
        return values;
    }
    
    int height () {
        return get_height(root);
    }
    
    int size () {
        return get_size(root);
    }

};


#endif /* avl_h */
