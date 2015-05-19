#ifndef __ACLTREE_H__
#define __ACLTREE_H__

#include "tree.h"

#define MAX(a,b) a>b?a:b 

TreeNode * singleRoLeft(TreeNode * node)
{
    if(node == NULL)
        return NULL;
    TreeNode * mid = node->left;
    node->left = mid->right;
    mid->right = node;
    
    node->height = MAX(Height(node->left), Height(node->right)) + 1;
    mid->height = MAX(Height(mid->left), Height(mid->right)) + 1;
 
    return mid;
}


TreeNode * singleRoRight(TreeNode * node)
{
    if(node == NULL)
        return NULL;

    TreeNode * mid = node->right;
    node->right = mid->left;
    mid->left = node;
    
    node->height = MAX(Height(node->left), Height(node->right)) + 1;
    mid->height = MAX(Height(mid->left), Height(mid->right)) + 1;
 
    return mid;
}


class AclTree : public Btree
{
    public:
          
} 





#endif
