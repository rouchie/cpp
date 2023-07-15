#ifndef _TREE_H_
#define _TREE_H_

// n 个节点的树，则有 n-1 条边，因为除了根节点外每个其他节点都有唯一一条边

// Binary Tree:             二叉树，最多只有2个子节点，左节点、右节点
// 完美二叉树
// Binary Search Tree(BST): 二叉搜索树
// 平衡二叉树

template <typename T>
struct Node {
    struct Node * left = nullptr;
    struct Node * right = nullptr;
    T value;
    Node(T v) : value(v) {}
};

#endif // _TREE_H_