//
// Created by Jacob Deep on 7/9/2016.
//

#include "max_heap.h"

MaxHeap::MaxHeap() {
    this->rootNode = NULL;
    this->maxHeapVector = new vector<node*>;
}

MaxHeap::~MaxHeap() {
 }

void MaxHeap :: defineNodePtrs(unsigned long position) {
    //root
    if (position == 1) return;
        //not root
    else {
        //left child
        if(position % 2 == 0) {
            this->maxHeapVector->at((position/2)-1)->left = this->maxHeapVector->at(position-1);
        }
            //right child
        else {
            this->maxHeapVector->at((position/2)-1)->right = this->maxHeapVector->at(position-1);
        }
        //define parent
        this->maxHeapVector->at(position-1)->parent = this->maxHeapVector->at((position/2)-1);

        //connect next child to parent
        this->defineNodePtrs(position-1);
    }
}

void MaxHeap::insert(int& key) {
    node *newNode;
    newNode = new node(key);
    this->setPtrsNull();
    this->maxHeapVector->push_back(newNode);
    this->topDown(this->maxHeapVector->size());
    this->defineNodePtrs(this->maxHeapVector->size());
}

void MaxHeap ::topDown(unsigned long position) {
    if (position == 1) return;
    else {
        //child > parent
        if(this->maxHeapVector->at(position-1)->key > this->maxHeapVector->at(((position)/2)-1)->key) {
            //swap child, parent keys
            int tempKey = this->maxHeapVector->at((position/2)-1)->key;
            this->maxHeapVector->at((position/2)-1)->key = this->maxHeapVector->at(position-1)->key;
            this->maxHeapVector->at(position-1)->key = tempKey;
            //compare parent w/ new key
            this->topDown((position+1)/2);
        }
            //child < parent
        else return;
    }
}

void MaxHeap ::setPtrsNull() {
    //define variables
    unsigned long i = 0;
    std::vector<node *>::iterator it;

    //iterate though heap
    for (it = this->maxHeapVector->begin(); it != this->maxHeapVector->end(); ++it, i++) {
        //set node ptrs to NULL
        this->maxHeapVector->at(i)->parent =
        this->maxHeapVector->at(i)->left =
        this->maxHeapVector->at(i)->right = NULL;
    }
}
void MaxHeap::postOrder(node *n, queue<node *> *path) {
    if(n != NULL) {

        this->postOrder(n->right,path);
        this->postOrder(n->left, path);
        path->push(n);

    }

}

void MaxHeap::preOrder(node *n, queue<node *> *path) {
    if (n != NULL) {

        path->push(n);
        preOrder(n->left, path);
        preOrder(n->right, path);
    }
}

void MaxHeap::inorder(node *n, queue<node *> *path) {
    if (n != NULL) {

        inorder(n->left, path);
        path->push(n);

        inorder(n->right, path);

    }

}

void MaxHeap::postOrder(queue<node *> *path) {
    this->postOrder(maxHeapVector->front(), path);
}

void MaxHeap::preOrder(queue<node *> *path) {
    this->preOrder(maxHeapVector->front(), path);
}

void MaxHeap::inorder(queue<node *> *path) {
    this->inorder(maxHeapVector->front(), path);
}
