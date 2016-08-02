//====================================================================
// binary_search_tree.h
// Author: sammaniamsam
//====================================================================
#include <iostream>
#include <queue>
#include "node.h"
//---------------------------------

#ifndef BINARY_SEARCH_TREE_BINARYSEARCHTREE_H
#define BINARY_SEARCH_TREE_BINARYSEARCHTREE_H

//---------------------------------
//struct node // structure for representing tree nodes
//{
//    int key;
//    unsigned int height;
//    node* left;
//    node* right;
//    node(int k) { key = k; left = right = NULL; height = 1; }
//};
//---------------------------------

class binary_search_tree
{

private:
    node *m_pRoot; //pointer to root node in BST

    void preorderTraversal(node *root, std::queue<node *> *path);
    void inorderTraversal(node *n, std::queue<node *> *path);
    void postorderTraversal(node *root, std::queue<node *> *path);
    void destroyTree(node *root);

    node *insert(node *key, node *n);
public:
    binary_search_tree();
    ~binary_search_tree();
    void insert(node *key);
    bool search(int& key, std::queue<node *> *path);
    bool removeNode(int key);
    void preorderTraversal(std::queue<node *> *path);
    void inorderTraversal(std::queue<node *> *path);
    void postorderTraversal(std::queue<node *> *path);
    void makeEmpty();
};

#endif //BINARY_SEARCH_TREE_BINARYSEARCHTREE_H
