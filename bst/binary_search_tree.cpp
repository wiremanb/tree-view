//====================================================================
// binary_search_tree.cpp
// Author: sammaniamsam
//====================================================================
#include "binary_search_tree.h"
//---------------------------------

//---------------------------------
//---------------------------------
//--------PRIVATE METHODS----------
//---------------------------------
//---------------------------------

//---------------------------------
//FUNCTION: destroyTree()
//PURPOSE: uses post-order traversal
//to destroy all nodes in the BST
//---------------------------------
void binary_search_tree::destroyTree(node *root)
{
    if (root == NULL) return;
    if (root->getLeft() != NULL)
        this->destroyTree(root->getLeft());
    if (root->getRight() != NULL)
        this->destroyTree(root->getRight());
    std::cout << "\nDeleting: " << root->getKey(); //TESTING
    delete root;
    return;
}

//---------------------------------
//FUNCTION: preorderTraversal()
//PURPOSE: Performs a pre-order
//traversal of the BST and stores
//route taken in path queue
//---------------------------------
void binary_search_tree::preorderTraversal(node *root, std::queue<node *> *path)
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
//traversal of the BST and stores
//route taken in path queue
//---------------------------------
void binary_search_tree::inorderTraversal(node *n, std::queue<node *> *path)
{
    if(n!=NULL)
    {
        inorderTraversal(n->getLeft(), path);
        if(n->getLeft() != NULL)
            n->getLeft()->setParent(n);
        if(n->getRight() != NULL)
            n->getRight()->setParent(n);
        path->push(n);
//        std::cout<<n->getKey()<<" ";
        inorderTraversal(n->getRight(), path);
    }
}

//---------------------------------
//FUNCTION: postorderTraversal()
//PURPOSE: Performs a post-order
//traversal of the BST and stores
//route taken in path queue
//---------------------------------
void binary_search_tree::postorderTraversal(node *root, std::queue<node *> *path)
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
//--------PUBLIC METHODS----------
//---------------------------------
//---------------------------------

//---------------------------------
//FUNCTION: binary_search_tree()
//PURPOSE: Initializes private
//member variable m_pRoot.
//---------------------------------
binary_search_tree::binary_search_tree()
{
    this->m_pRoot = NULL;
}

//---------------------------------
//FUNCTION: ~binary_search_tree()
//PURPOSE: Calls private fctn DestroyTree
//and passes in the private member variable
//m_pRoot.
//---------------------------------
binary_search_tree::~binary_search_tree()
{
    this->destroyTree(this->m_pRoot);
}

//---------------------------------
//FUNCTION: insert()
//PURPOSE: Creates a new node and
//assigns it a key. Then, searches
//for a position within the binary
//tree to insert the new node.
//---------------------------------
void binary_search_tree::insert(node *key)
{
    this->m_pRoot = insert(key, this->m_pRoot);
    this->m_pRoot->setParent(NULL);
}

node* binary_search_tree::insert(node* key, node* n)
{
    // Am I root??
    if(n == NULL)
        n = key;
    // Go left!
    else if(key->getKey() < n->getKey())
    {
        n->setLeft(insert(key, n->getLeft()));
        n->getLeft()->setParent(n);
    }
    // Go right!
    else if(key->getKey() > n->getKey())
    {
        n->setRight(insert(key, n->getRight()));
        n->getRight()->setParent(n);
    }
    return n;
}

//---------------------------------
//FUNCTION: search()
//PURPOSE: Looks for node in BST
//that has the same key as the
//key argument passed in. The queue
//argument passed in stores the
//traversal path. Finally, if no
//match is found then false is
//returned
//---------------------------------
bool binary_search_tree::search(int& key, std::queue<node *> *path)
{
    //define variables
    node *temp;
    temp = m_pRoot;
    path->push(temp);

    //search for key in BST
    while((temp != NULL) && (key != temp->getKey()))
    {
        if(key < temp->getKey())
            temp = temp->getLeft();
        else
            temp = temp->getRight();
        path->push(temp);
    }

    //did not find key
    if(temp == NULL)
    {
        std::cout << "\n" << "Key: " << key << " not found" << "\n";//TESTING
        return false;
    }
    else
        return true;
}

//---------------------------------
//FUNCTION: preorderTraversal()
//PURPOSE: Calls private fctn
//preorderTraversal() and passes
//it queue that stores the traversal
//path.
//---------------------------------
void binary_search_tree::preorderTraversal(std::queue<node *> *path)
{
    this->preorderTraversal(this->m_pRoot, path);
}

//---------------------------------
//FUNCTION: inorderTraversal()
//PURPOSE: Calls private fctn
//inorderTraversal() and passes
//it queue that stores the traversal
//path.
//---------------------------------
void binary_search_tree::inorderTraversal(std::queue<node *> *path)
{
    this->inorderTraversal(this->m_pRoot, path);
}

//---------------------------------
//FUNCTION: postorderTraversal()
//PURPOSE: Calls private fctn
//postorderTraversal() and passes
//it queue that stores the traversal
//path.
//---------------------------------
void binary_search_tree::postorderTraversal(std::queue<node *> *path)
{
    this->postorderTraversal(this->m_pRoot, path);
}

void binary_search_tree::makeEmpty()
{
    this->m_pRoot = NULL;
}

//---------------------------------
//FUNCTION: removeNode()
//PURPOSE: Removes a single node
//from the BST. Two cases:
//Case 1 -- delete node with no
//          children or one child
//Case 2 -- delete node with two
//          children
//---------------------------------
bool binary_search_tree::removeNode(int key)
{
    //define variables
    node *back, *temp, *delParent, *delNode;
    temp = m_pRoot, back = NULL;

    //search for node to delete
    while((temp != NULL) && (key != temp->getKey()))
    {
        back = temp;
        if(key < temp->getKey())
            temp = temp->getLeft();
        else
            temp = temp->getRight();
    }

    //didn't find the node to remove
    if(temp == NULL)
    {
        std::cout << "\n" << "key: " << key << " was not found" << "\n";//TESTING
        return false;
    }

    //found node to remove
    else
    {
        //deleting the root
        if(temp == m_pRoot)
        {
            delNode = m_pRoot;
            delParent = NULL;
        }
        else
        {
            delNode = temp;
            delParent = back;
        }
    }
    //- - - - - - - - - - - - - - - - - - - - - - - - - -
    //Case 1: Deleting node with no children or one child
    //- - - - - - - - - - - - - - - - - - - - - - - - - -
    //node to delete has left child
    if (delNode->getRight() == NULL)
    {
        //if deleting root
        if(delParent == NULL)
        {
            m_pRoot = delNode->getLeft();
            delete delNode;
            return true;
        }
        else
        {
            if(delParent->getLeft() == delNode)
                delParent->setLeft(delNode->getLeft());
            else
                delParent->setRight(delNode->getLeft());
            delete delNode;
            return true;
        }
    }
    //node to delete has right child
    else
    {
        if(delNode->getLeft() == NULL)
        {
            //if deleting root
            if(delParent == NULL)
            {
                m_pRoot = delNode->getRight();
                delete delNode;
                return true;
            }
            else
            {
                if(delParent->getLeft() == delNode)
                    delParent->setLeft(delNode->getRight());
                else
                    delParent->setRight(delNode->getRight());
                delete delNode;
                return true;
            }
        }
        //- - - - - - - - - - - - - - - - - - - -
        //Case 2: Deleting node with two children
        //- - - - - - - - - - - - - - - - - - - -
        else
        {
            temp = delNode->getLeft();
            back = delNode;

            //get the largest node in
            //delNode's left child's subtree
            while(temp->getRight() != NULL)
            {
                back = temp;
                temp = temp->getRight();
            }
            //Copy the replacement value(s) into the node to be removed
            delNode->setKey(temp->getKey());

            //Remove the replacement node from the tree
            if(back == delNode)
                back->setLeft(temp->getLeft());
            else
                back->setRight(temp->getLeft());
            delete temp;
            return true;
        }//end Case 2
    }
}
