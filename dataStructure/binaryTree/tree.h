#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

class TreeNode
{
    public:
        typedef TreeNode * ptrParent;
        typedef TreeNode * ptrChild;
        ptrParent parent;
        ptrChild leftChild;
        ptrChild rightChild;
        int data;
        int count;
        int height; 
        TreeNode() : parent(NULL), leftChild(NULL), 
                     rightChild(NULL), count(0), height(0){}
        TreeNode(int value) : parent(NULL), leftChild(NULL), 
                              data(value), count(1), rightChild(NULL), 
                              height(0){}
};

typedef pair<TreeNode *, int> TYPE;

int Height(TreeNode * node)
{
    if(node == NULL)
        return -1;
    else
        return node->height; 
}        

class Btree
{
    public:
        
        TreeNode * root;
    
        virtual bool tree_insert(int, TreeNode **) = 0;
        virtual bool tree_insert(int, TreeNode **, TreeNode *) = 0;
        virtual void tree_delete(int, TreeNode **) = 0; 
        virtual TreeNode * find(int, TreeNode *) = 0;

        vector<TYPE> level_travel(TreeNode *); 
        void first_travel(TreeNode *); 
        void last_travel(TreeNode *); 
        void middle_travel(TreeNode *);
        void printNode(TreeNode *); 
        void printLevel(vector<TYPE>);
        TreeNode * clean(TreeNode *);
         
 
        Btree() : root(NULL) {}

};

TreeNode * Btree :: clean(TreeNode * node)
{
    if(node != NULL)
    {
        clean(node->leftChild);
        clean(node->rightChild);
        delete node;
    }
    return NULL; 
}

void Btree :: printNode(TreeNode * node)
{
    for(int i = 0; i < node->count; i++)
        std::cout << node->data << std::endl;
}

void Btree :: printLevel(vector<TYPE> res)
{
    int level = res[0].second;
    
    cout << "level travel show" << endl;
    for(int i = 0; i < res.size(); i++)
    {
        TYPE tmp = res[i];
        
        if( level != tmp.second)
        {
            cout << endl << endl;
            level = tmp.second;
        }

        if(tmp.first != NULL)
        {
            cout << tmp.first->data << " ";
        }
        else
        {
            cout << "nu ";
        }
    }
}

void Btree :: middle_travel(TreeNode * node)
{
    if(node == NULL) 
        return;
 
    middle_travel(node->leftChild);
    printNode(node);
    middle_travel(node->rightChild);
}

void Btree :: first_travel(TreeNode * node)
{
    if(node == NULL) 
        return;
 
    printNode(node);
    first_travel(node->leftChild);
    first_travel(node->rightChild);
}

void Btree :: last_travel(TreeNode * node)
{
    if(node == NULL) 
        return;
 
    last_travel(node->leftChild);
    last_travel(node->rightChild);
    printNode(node);
}

vector<TYPE> Btree :: level_travel(TreeNode * node)
{
    queue<TYPE> q;
    vector<TYPE> res;
    q.push(make_pair(node, 1));
    while(!q.empty())
    {
        TYPE tmp = q.front();
        q.pop();
        res.push_back(tmp);

        if(tmp.first == NULL)
            continue;
        
        TreeNode * null = NULL;
        if(tmp.first->leftChild == NULL)
            q.push(make_pair(null, tmp.second +1));
        else
            q.push(make_pair(tmp.first->leftChild, tmp.second + 1));
        
        if(tmp.first->rightChild == NULL)
            q.push(make_pair(null, tmp.second +1));
        else
            q.push(make_pair(tmp.first->rightChild, tmp.second + 1));
    }   
    return res;  
}

class SearchTree : public Btree
{
    public:
    bool tree_insert(int value, TreeNode ** ptrNode)
    {
        TreeNode * node = *ptrNode;
        if(*ptrNode == NULL)
        {
            *ptrNode = new TreeNode(value);

            if(*ptrNode == NULL)
                return false;
        }
        else if(value < node->data)
            tree_insert(value, &(node->leftChild)); 
        else if(value > node->data)
            tree_insert(value, &(node->rightChild));
        else
            node->count++;
        return true;
    }

    bool tree_insert(int value, TreeNode ** ptrNode, TreeNode * parent)
    {
        TreeNode * node = *ptrNode;
        if(*ptrNode == NULL)
        {
            *ptrNode = new TreeNode(value);
            
            if(*ptrNode == NULL)
                return false;

            (*ptrNode)->parent = parent;

        }
        else if(value < node->data)
            tree_insert(value, &(node->leftChild), node); 
        else if(value > node->data)
            tree_insert(value, &(node->rightChild), node);
        else
            node->count++;
        return true;
    }

    TreeNode * findMin(TreeNode * node)
    {
        if(node == NULL)
            return NULL;
        if(node->leftChild != NULL)
            findMin(node->leftChild);
        else
            return node;
    }

    TreeNode * findMax(TreeNode * node)
    {
        if(node == NULL)
            return NULL;
        if(node->rightChild != NULL)
            findMax(node->rightChild);
        else
            return node;
    }

    TreeNode * find(int value, TreeNode * node)
    {
        if(node == NULL)
            return NULL;
        if(value > node->data)
            find(value, node->rightChild);
        else if(value < node->data)
            find(value, node->leftChild);
        else
            return node;
    }

    bool pathByParent(TreeNode * node)
    {
        if(node == NULL)
            return false;
        if(node->parent != NULL)
            pathByParent(node->parent);
        std::cout << node->data << "->" << std::endl;  
    }

    void tree_delete(int value, TreeNode ** ptrNode)
    {
        if(ptrNode == NULL)
            return;
        TreeNode * node = *ptrNode;

        if(value > node->data)
            tree_delete(value, &(node->rightChild));
        else if(value < node->data)
            tree_delete(value, &(node->leftChild));
        else
        {
            if(node->leftChild == NULL || node->rightChild == NULL)
            {
                if(node->leftChild != NULL)
                    *ptrNode = node->leftChild;
                if(node->rightChild != NULL)
                    *ptrNode = node->rightChild;
                free(node);
            }
            else
            {
                TreeNode * tmp = findMin(node->rightChild);
                node->data = tmp->data;
                node->count = tmp->count;
                tree_delete(tmp->data, &(node->rightChild));
            }
        }
        return; 
    }

};


#endif

