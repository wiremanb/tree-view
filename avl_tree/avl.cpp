#include "avl_tree/avl.h"

AVL::AVL()
{

    this->_root = NULL;
}

AVL::~AVL()
{

}

int AVL::countNodes(node *n)
{
    if(n==NULL)
        return 0;
    else
    {
        int cnt = 1;
        cnt += this->countNodes(n->getLeft());
        cnt += this->countNodes(n->getRight());
        return cnt;
    }
}

void AVL::postorder(node *n, std::queue<node *> *path)
{

}

void AVL::preorder(node *n, std::queue<node *> *path)
{
    if(n!=NULL)
    {
        //        std::cout << n->key << " ";
        path->push(n);
        n->getLeft()->setParent(n);
        n->getRight()->setParent(n);
        preorder(n->getLeft(), path);
        preorder(n->getRight(), path);
    }
}

void AVL::inorder(node *n, std::queue<node*>* path)
{
    if(n!=NULL)
    {
        inorder(n->getLeft(), path);
        if(n->getLeft() != NULL)
            n->getLeft()->setParent(n);
        if(n->getRight() != NULL)
            n->getRight()->setParent(n);
        path->push(n);
//        std::cout<<n->getKey()<<" ";
        inorder(n->getRight(), path);
    }
}

bool AVL::search(int val, node *n)
{

}

node *AVL::insert(node *key, node *n)
{
    // If there are no other nodes..
    if(n==NULL)
        n = key;
    // Go left young man!
    else if(key->getKey()<n->getKey())
    {
        // Recursively place the node where it belongs
        n->setLeft(insert(key, n->getLeft()));
        // Rebalance after the node has been added
        if(this->getHeight(n->getLeft())-this->getHeight(n->getRight()) == 2)
        {

            if(key->getKey()<n->getLeft()->getKey())
                n = rotateLeftChild(n);
            else
                n = doubleLeftChild(n);
        }
        n->getLeft()->setParent(n);
    }
    // Go right young man!
    else if(key->getKey()>n->getKey())
    {
        // Recursively place the node where it belongs
        n->setRight(insert(key, n->getRight()));
        // Rebalance after the node has been added
        if(this->getHeight(n->getRight())-this->getHeight(n->getLeft()) ==2)
        {
            if(key->getKey()>n->getRight()->getKey())
                n = rotateRightChild(n);
            else
                n = doubleRightChild(n);
        }
        n->getRight()->setParent(n);
    }
    n->setHeight(this->getMax(this->getHeight(n->getLeft()), this->getHeight(n->getRight())) + 1);
    return n;
}

void AVL::makeEmpty()
{
    this->_root = NULL;
}

void AVL::insert(node *key)
{
    this->_root = this->insert(key, this->_root);
    this->_root->setParent(NULL);
}

void AVL::inorder(std::queue<node *> *path)
{
    inorder(this->_root,path);
}

void AVL::preorder(std::queue<node *> *path)
{
    preorder(this->_root, path);
}

void AVL::postorder(std::queue<node *> *path)
{

}

bool AVL::isEmpty()
{
    return (this->_root==NULL);
}

bool AVL::search(int val, std::queue<node *> *path)
{

}

int AVL::getHeight(node *n)
{
    return (n==NULL ? -1 : n->getHeight());
}

int AVL::getMax(int left, int right)
{
    return (left>right ? left : right);
}

int AVL::countNodes()
{
    return countNodes(this->_root);
}

// Left heavy (LL)
node *AVL::rotateLeftChild(node *n)
{
    node* tmpNode = n->getLeft();
    n->setLeft(tmpNode->getRight());
    tmpNode->setRight(n);
    n->setParent(tmpNode);
    n->setHeight(this->getMax(this->getHeight(n->getLeft()), this->getHeight(n->getRight())) + 1);
    tmpNode->setHeight(this->getMax(this->getHeight(tmpNode->getLeft()), n->getHeight()) + 1);
    return tmpNode;
}

// Right heavy (RR)
node *AVL::rotateRightChild(node *n)
{
    node* tmpNode = n->getRight();
    n->setRight(tmpNode->getLeft());
    tmpNode->setLeft(n);
    n->setParent(tmpNode);
    n->setHeight(this->getMax(this->getHeight(n->getLeft()), this->getHeight(n->getRight())) + 1);
    tmpNode->setHeight(this->getMax(this->getHeight(tmpNode->getRight()), n->getHeight()) + 1);
    return tmpNode;
}

// (LR)
node *AVL::doubleLeftChild(node *n)
{
    n->setLeft(rotateRightChild(n->getLeft()));
    return rotateLeftChild(n);
}

// (RL)
node *AVL::doubleRightChild(node *n)
{
    n->setRight(rotateLeftChild(n->getRight()));
    return rotateRightChild(n);
}

