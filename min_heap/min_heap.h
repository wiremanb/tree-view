//====================================================================
// min_heap.h
// Author: sammaniamsam
//====================================================================
#include <iostream>
#include <vector>
#include <queue>
//---------------------------------
#include "node.h"
//---------------------------------

#ifndef ALGORITHM_DRAWER_MIN_HEAP_H
#define ALGORITHM_DRAWER_MIN_HEAP_H

//---------------------------------
/*struct node // the structure for representing tree nodes
{
    int key;
    unsigned int height;
    node* left;
    node* right;
    node* parent;
    node(int k) { key = k; left = right = parent = NULL; height = 1; }
};*/
//---------------------------------

class min_heap
{
    private:
        std::vector<node *>* minHeapVector; //ptr to min heap

        void topDown (unsigned long position);
        void defineNodePtrs(unsigned long position);
        void setPtrsNull();
        void preorderTraversal(node *root, std::queue<node *> *path);
        void inorderTraversal(node *root, std::queue<node *> *path);
        void postorderTraversal(node *root, std::queue<node *> *path);

    public:
        min_heap();
        ~min_heap();
        void insert(node* newNode);
        bool search(int& key, std::queue<node *> *path);
        bool removeNode();
        void preorderTraversal(std::queue<node *> *path);
        void inorderTraversal(std::queue<node *> *path);
        void postorderTraversal(std::queue<node *> *path);
        //breadthFirstSearch()
};

#endif //ALGORITHM_DRAWER_HEAP_H
