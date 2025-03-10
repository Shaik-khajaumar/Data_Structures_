//
//  TreeNode.h
//  DataStructures
//
//  Created by Shaik on 25/01/25.
//

#ifndef TreeNode_h
#define TreeNode_h

template <typename T>
class TreeNode {
public:
    T key;
    TreeNode<T>* left {nullptr};
    TreeNode<T>* right {nullptr};
    
    TreeNode (T value) : key(value), left (nullptr), right (nullptr) {}
};
#endif /* TreeNode_h */
