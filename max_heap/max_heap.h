//
// Created by Jacob Deep on 7/9/2016.
//

#include <queue>
#include <vector>
#include <iostream>

#ifndef HEAPSORT_H
#define HEAPSORT_H

using namespace std;

struct node {
    int key;
    node* left;
    node* right;
    node* parent;
    unsigned char height;
    node(int k) {key = k; parent = left = right = NULL; height = 0;}
};

class MaxHeap {
    private:
        node* rootNode;
        vector<node*> *maxHeapVector;
        void topDown (unsigned long position);
        void defineNodePtrs(unsigned long position);
        void setPtrsNull();
        void postOrder(node* n, queue<node*> *path);
        void preOrder(node* n, queue<node*> *path);
        void inorder(node* n, queue<node*> *path);



    public:
        MaxHeap();
        ~MaxHeap();
        void inorder(queue<node*> *path);
        void preOrder(queue<node*> *path);
        void postOrder(queue<node*> *path);
        bool search(int& key, std::queue<node *> *path);
        bool removeNode();
        void insert(int& key);

};


#endif
