#ifndef AVL_H
#define AVL_H

#include <queue>
#include <iostream>
#include "../node.h"

//struct node // the structure for representing tree nodes
//{
//    int key;
//    unsigned char height;
//    node* left;
//    node* right;
//    node(int k) { key = k; left = right = NULL; height = 1; }
//};

class AVL
{
private:
    node* _root;

    int countNodes(node* n);
    void postorder(node* n, std::queue<node *> *path);
    void preorder(node* n, std::queue<node *> *path);
    void inorder(node* n, std::queue<node *> *path);
    bool search(int val, node* n);
    node *insert(node* key, node* n);

public:
    AVL();
    ~AVL();
    void makeEmpty();
    void insert(node* key);
    void inorder(std::queue<node*>* path);
    void preorder(std::queue<node*>* path);
    void postorder(std::queue<node*>* path);
    bool isEmpty();
    bool search(int val, std::queue<node*>* path);
    int getHeight(node* n);
    int getMax(int left, int right);
    int countNodes();
    node *rotateLeftChild(node* n);
    node *rotateRightChild(node* n);
    node *doubleLeftChild(node* n);
    node *doubleRightChild(node* n);
};

#endif // AVL_H
