//====================================================================
// min_heap.cpp
// Author: sammaniamsam
//====================================================================
#include "min_heap.h"
//---------------------------------

//---------------------------------
//---------------------------------
//--------PRIVATE METHODS----------
//---------------------------------
//---------------------------------

//---------------------------------
//FUNCTION: topDown()
//PURPOSE: Recursive top-down re-heap
//function that compares a child to
//its' parent. Each child must be
//greater than its' parent.
//---------------------------------
void min_heap::topDown(unsigned long position) {

    //root
    if (position == 1) return;
    //not root
    else {
        //child < parent
        if(this->minHeapVector->at(position-1)->getKey() < this->minHeapVector->at((position/2)-1)->getKey()) {
            //swap child, parent keys
            int tempKey = this->minHeapVector->at(position-1)->getKey();
            this->minHeapVector->at(position-1)->setKey(this->minHeapVector->at((position/2)-1)->getKey());
            this->minHeapVector->at((position/2)-1)->setKey(tempKey);// = tempKey;
            //compare parent w/ new key
            this->topDown(position/2);
        }
        //child > parent
        else return;
    }
}

//---------------------------------
//FUNCTION: defineNodePtrs()
//PURPOSE: Recursive function that
//iterates backwards over the
//heap and defines every parents'
//ptrs. Since this heap is a complete
//binary tree, nodes at an
//even position are left children, and
//nodes at an odd position are right
//children.
//---------------------------------
void min_heap::defineNodePtrs(unsigned long position) {

    //root
    if (position == 1) return;
    //not root
    else {
        //left child
        if(position % 2 == 0) {
            this->minHeapVector->at((position/2)-1)->setLeft(this->minHeapVector->at(position-1));
        }
        //right child
        else {
            this->minHeapVector->at((position/2)-1)->setRight(this->minHeapVector->at(position-1));
        }
        //define parent
        this->minHeapVector->at(position-1)->setParent(this->minHeapVector->at((position/2)-1));

        //connect next child to parent
        this->defineNodePtrs(position-1);
    }
}

//---------------------------------
//FUNCTION: setPtrsNull()
//PURPOSE: Sets left and right ptrs
//for each node to NULL.
//---------------------------------
void min_heap::setPtrsNull() {

    //define variables
    unsigned long i = 0;
    std::vector<node *>::iterator it;

    //iterate though heap
    for (it = this->minHeapVector->begin(); it != this->minHeapVector->end(); ++it, i++) {
        //set node ptrs to NULL
        this->minHeapVector->at(i)->setParent(NULL);
        this->minHeapVector->at(i)->setLeft(NULL);
        this->minHeapVector->at(i)->setRight(NULL);
    }
}

//---------------------------------
//FUNCTION: preorderTraversal()
//PURPOSE: Performs a pre-order
//traversal of the heap and stores
//route taken in path queue.
//---------------------------------
void min_heap::preorderTraversal(node *root, std::queue<node *> *path)
{
    if(root != NULL)
    {
        path->push(root);
        this->preorderTraversal(root->getLeft(), path);
        this->preorderTraversal(root->getRight(), path);
    }
}

//---------------------------------
//FUNCTION: inorderTraversal()
//PURPOSE: Performs a in-order
//traversal of the heap and stores
//route taken in path queue.
//---------------------------------
void min_heap::inorderTraversal(node *root, std::queue<node *> *path)
{
    if(root != NULL)
    {
        this->inorderTraversal(root->getLeft(), path);
        path->push(root);
        this->inorderTraversal(root->getRight(), path);
    }
}

//---------------------------------
//FUNCTION: postorderTraversal()
//PURPOSE: Performs a post-order
//traversal of the heap and stores
//route taken in path queue.
//---------------------------------
void min_heap::postorderTraversal(node *root, std::queue<node *> *path)
{
    if(root != NULL)
    {
        this->postorderTraversal(root->getLeft(), path);
        this->postorderTraversal(root->getRight(), path);
        path->push(root);
    }
}

//---------------------------------
//---------------------------------
//--------PUBLIC METHODS-----------
//---------------------------------
//---------------------------------

//---------------------------------
//FUNCTION: min_heap()
//PURPOSE: Initialize private member
//variable
//---------------------------------
min_heap::min_heap() {

    this->minHeapVector = new std::vector<node *>;
}

//---------------------------------
//FUNCTION: ~min_heap()
//PURPOSE: Deletes all dynamically
//created instances of node and
//vector
//---------------------------------
min_heap::~min_heap() {

    //define variables
    node* nPtr;

    //set node ptrs to null
    this->setPtrsNull();

    //deallocate memory to dynamic instances
    while(!this->minHeapVector->empty()) {
        nPtr = this->minHeapVector->back();
        delete nPtr;
        this->minHeapVector->pop_back();
    }
    delete this->minHeapVector; this->minHeapVector = NULL;
}

//---------------------------------
//FUNCTION: insert()
//PURPOSE: Inserts node into heap then re-heaps.
//---------------------------------
void min_heap::insert(node* newNode) {

    //initialize node ptrs to null
    this->setPtrsNull();

    //add newNode to heap vector
    this->minHeapVector->push_back(newNode);
    //heapify using top down
    this->topDown(this->minHeapVector->size());
    //define heap nodes' ptrs
    this->defineNodePtrs(this->minHeapVector->size());
}

//---------------------------------
//FUNCTION: removeNode()
//PURPOSE: Deletes the heap's root
//node and then re-heaps.
//Returns false if heap is empty.
//---------------------------------
bool min_heap::removeNode() {

    //define variables
    node *leaf, *delNode;
    //initialize node ptrs to null
    this->setPtrsNull();

    if(!this->minHeapVector->empty()) {
        //get last leaf
        leaf = this->minHeapVector->back();
        //set leaf ptrs to NULL
        leaf->setLeft(NULL), leaf->setRight(NULL);
        //swap last leaf and root
        delNode = this->minHeapVector->back() = this->minHeapVector->front();
        this->minHeapVector->front() = leaf;
        //delete last leaf
        delNode->setLeft(NULL), delNode->setRight(NULL); delete delNode;
        this->minHeapVector->pop_back();
        //heapify using top down
        this->topDown((this->minHeapVector->size()+1)/2);
        //define heap nodes' ptrs
        this->defineNodePtrs(this->minHeapVector->size());
        return true;
    }
    //heap is empty
    else return false;
}

//---------------------------------
//FUNCTION: search()
//PURPOSE: Searches for key in heap
//and stores traversal route in
//queue. Traversal time O(n).
//Returns false if key is not found.
//---------------------------------
bool min_heap::search(int& key, std::queue<node *> *path) {

    //define variables
    unsigned long i = 0;
    std::vector<node *>::iterator it;

    //search for key
    for(it = this->minHeapVector->begin(); it != this->minHeapVector->end(); ++it, i++) {
        //record search path
        path->push(this->minHeapVector->at(i));
        //key found
        if(this->minHeapVector->at(i)->getKey() == key) return true;
    }
    //key not found
    return false;
}

//---------------------------------
//FUNCTION: preorderTraversal()
//PURPOSE: Passes queue to recursive
//private fctn preorderTraversal()
//---------------------------------
void min_heap::preorderTraversal(std::queue<node *> *path) {

    this->preorderTraversal(this->minHeapVector->front(), path);
}

//---------------------------------
//FUNCTION: inorderTraversal()
//PURPOSE: Passes queue to recursive
//private fctn inorderTraversal()
//---------------------------------
void min_heap::inorderTraversal(std::queue<node *> *path) {

    this->inorderTraversal(this->minHeapVector->front(), path);
}

//---------------------------------
//FUNCTION: postorderTraversal()
//PURPOSE: Passes queue to recursive
//private fctn postorderTraversal()
//---------------------------------
void min_heap::postorderTraversal(std::queue<node *> *path) {

    this->postorderTraversal(this->minHeapVector->front(), path);
}

