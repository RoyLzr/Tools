#ifndef __ACLTREE_H__
#define __ACLTREE_H__

#include "tree.h"

#define MAX(a,b) a>b?a:b 

TreeNode * singleRoLeft(TreeNode * node)
{
    if(node == NULL)
        return NULL;
    TreeNode * mid = node->leftChild;
    node->leftChild = mid->rightChild;
    mid->rightChild = node;
    
    node->height = MAX(Height(node->leftChild), Height(node->rightChild)) + 1;
    mid->height = MAX(Height(mid->leftChild), Height(mid->rightChild)) + 1;
 
    return mid;
}


TreeNode * singleRoRight(TreeNode * node)
{
    if(node == NULL)
        return NULL;

    TreeNode * mid = node->rightChild;
    node->rightChild = mid->leftChild;
    mid->leftChild = node;
    
    node->height = MAX(Height(node->leftChild), Height(node->rightChild)) + 1;
    mid->height = MAX(Height(mid->leftChild), Height(mid->rightChild)) + 1;
 
    return mid;
}

TreeNode * doubleRoLeft(TreeNode * node)
{
    node->leftChild = singleRoRight(node->leftChild);
    node = singleRoLeft(node);
    return node;
}

TreeNode * doubleRoRight(TreeNode * node)
{
    node->rightChild = singleRoLeft(node->rightChild);
    node = singleRoRight(node);
    return node;
}


class AvlTree : public SearchTree
{
    public:
        virtual bool tree_insert(int value, TreeNode **); 
          
}; 

bool AvlTree :: tree_insert(int value, TreeNode ** ptrNode)
{
    if(ptrNode == NULL)
        return false;
    TreeNode * node = *ptrNode;
    if(*ptrNode == NULL)
    {
        *ptrNode = new TreeNode(value); 
    }
    else if(value < node->data)
    {
        tree_insert(value, &(node->leftChild));
        if(Height(node->leftChild) - Height(node->rightChild) == 2)
        {
            if(value < node->leftChild->data)
                *ptrNode = singleRoLeft(node);
            else
                *ptrNode = doubleRoLeft(node);
        } 
    }
    else if(value > node->data)
    {
        tree_insert(value, &(node->rightChild));
        if(Height(node->rightChild) - Height(node->leftChild) == 2)
        {
            if(value > node->rightChild->data)
                *ptrNode = singleRoRight(node);
            else
                *ptrNode = doubleRoRight(node);
        }
    }
    //new TreeNode, node is NULL
    if(node == NULL)
        node = *ptrNode;

    node->height = MAX(Height(node->leftChild), Height(node->rightChild)) + 1;
    return true; 
}

#endif
