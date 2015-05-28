#ifndef __ACLTREE_H__
#define __ACLTREE_H__

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef enum ColorType {RED, BLACK} ColorType;
#define NEGTIVE -99999
#define MAX(a,b) a>b?a:b 

class RbNode
{
    public:
        int data;
        RbNode * left;
        RbNode * right;
        RbNode * parent;
        ColorType color;
    RbNode(int value) : data(value), 
                        left(NULL), right(NULL) {}

    RbNode() : left(NULL), right(NULL) {}
    
};


typedef pair<RbNode *, int> TYPE;

RbNode * singleRoLeft(RbNode * node)
{
    if(node == NULL)
        return NULL;
    
    RbNode * mid = node->left;
    node->left = mid->right;
    mid->right = node;
   
    mid->parent = mid->right->parent;
    mid->right->parent = mid;
    mid->left->parent = mid;
    node->left->parent = node;   
    
    return mid;
}


RbNode * singleRoRight(RbNode * node)
{
    if(node == NULL)
        return NULL;

    RbNode * mid = node->right;
    node->right = mid->left;
    mid->left = node;

    mid->parent = mid->left->parent;
    mid->left->parent = mid;
    mid->right->parent = mid;
    node->right->parent = node;    

    return mid;
}

RbNode * doubleRoLeft(RbNode * node)
{
    node->left = singleRoRight(node->left);
    node = singleRoLeft(node);
    return node;
}

RbNode * doubleRoRight(RbNode * node)
{
    node->right = singleRoLeft(node->right);
    node = singleRoRight(node);
    return node;
}

//red black tree, NullPoint is used to detect NULL
//head is used in RbTree, head->right point to root
class RbTree
{
    public:
        RbNode * head;
        RbNode * NullNode;
        RbTree()
        {
            NullNode = new RbNode();
            NullNode->left = NullNode;
            NullNode->right = NullNode;
            NullNode->color = BLACK;
            
            head = new RbNode(NEGTIVE);
            head->color = BLACK;
            head->left = NullNode;
            head->right = NullNode;
            head->parent = NullNode; 
        }
};

RbNode *tmp, *parent, *Gp, *GGp;
void AdjustRb(int item, RbNode * head)
{
    tmp->color = RED;
    tmp->left->color = BLACK;
    tmp->right->color = BLACK;
    
    RbNode ** GGpTmp;
    if(item < GGp->data)
        GGpTmp = &(GGp->left);
    else
        GGpTmp = &(GGp->right);

    if(parent->color == RED) 
    {
        Gp->color = RED;
        if((item < Gp->data) != (item < parent->data))  
        {
            if(item < Gp->data && item > parent->data)
                tmp = doubleRoLeft(Gp); 
            else 
                tmp = doubleRoRight(Gp); 
        }
        else
        {
            if(item < Gp->data)
                tmp = singleRoLeft(Gp); 
            else 
                tmp = singleRoRight(Gp); 
        }
        tmp->color = BLACK;
        //refresh when tmp point is changed
        //only change color do not need change

        *GGpTmp = tmp;

        //tmp is move high, when use p,Gp. they has been refreshed
    }
    head->right->color = BLACK;
}

RbTree * RbInsert(int value, RbTree * tree)
{
    tree->NullNode->data = value;
    tmp = tree->head;
    GGp = Gp = parent = tmp; 
    while(tmp->data != value && tmp != tree->NullNode) 
    {
        GGp = Gp;
        Gp = parent;
        parent = tmp;
        if(value > tmp->data)
            tmp = tmp->right;
        else 
            tmp = tmp->left;
        if(tmp->left->color == RED && tmp->right->color == RED)
            AdjustRb(value, tree->head);
    }
    
    if(tmp != tree->NullNode)
    {
        return NULL;
    }
    
    //tmp == NullNode, parent add node
    tmp = new RbNode(value);
    tmp->color = RED; 
    tmp->left = tree->NullNode; 
    tmp->right = tree->NullNode;
    tmp->parent = parent;
     
    if(value < parent->data)
        parent->left = tmp;
    else
        parent->right = tmp;
    
    AdjustRb(value, tree->head);
    
    return tree;     
}



void printLevel(vector<TYPE> res)
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
            cout << tmp.first->data << "("<<tmp.first->color <<","<<tmp.first->parent->data <<")"<<" ";
        }
        else
        {
            cout << "nu ";
        }
    }
}

vector<TYPE>  level_travel(RbTree * tree)
{
    RbNode * node = tree->head->right;
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
        
        RbNode * null = NULL;
        if(tmp.first->left == tree->NullNode)
            q.push(make_pair(null, tmp.second +1));
        else
            q.push(make_pair(tmp.first->left, tmp.second + 1));
        
        if(tmp.first->right == tree->NullNode)
            q.push(make_pair(null, tmp.second +1));
        else
            q.push(make_pair(tmp.first->right, tmp.second + 1));
    }   
    return res;  
}

void middleTravel(RbNode * node, RbNode * NullNode)
{
    if(node == NullNode)
        return;
    middleTravel(node->left, NullNode);
    cout << node->data << endl;
    middleTravel(node->right, NullNode);
}

RbNode * find(int key, RbNode * node, RbNode * NullNode)
{
    if(node == NullNode)
        return NULL;
    RbNode * res = node;

    if(key < node->data)
        res = find(key, node->left, NullNode);
    else if(key > node->data)
        res = find(key, node->right, NullNode);
    
    return res;
}

RbNode * findMin(RbNode * node, RbNode * NullNode)
{
    if(node == NullNode)
        return NULL;
    while(node->left != NullNode)
        node = node->left;
    
    return node; 
}

void DeleteFix(RbNode * node, RbTree * tree)
{
    RbNode * root = tree->head->right;
    while(node != root && node->color != RED)
    {
        RbNode ** tmp;
        RbNode * tmpParent;
        if(node == node->parent->left)
        {
            cout << "===========step in left==========" << endl;
            RbNode * brother = node->parent->right;
            if(brother->color == RED)
            {
                tmpParent = node->parent->parent;
                if(tmpParent->left == node->parent)
                    tmp = &(tmpParent->left);
                else
                    tmp = &(tmpParent->right);
                 
                node->parent->color = RED;
                brother->color = BLACK; 
                (*tmp) = singleRoRight(node->parent);
                (*tmp)->parent = tmpParent;
            }
            else
            {
                if(brother->left->color == BLACK && brother->right->color == BLACK)
                {
                    brother->color = RED;
                    node = node->parent;
                }
                else if(brother->left->color == RED && brother->right->color == BLACK)
                {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    node->parent->right = singleRoLeft(brother);
                }
                else if(brother->right->color == RED)
                {
                    tmpParent = node->parent->parent;
                    if(tmpParent->left == node->parent)
                        tmp = &(tmpParent->left);
                    else
                        tmp = &(tmpParent->right); 
                    
                    node->parent->color = BLACK;
                    brother->color = node->parent->color;
                    brother->right->color = BLACK;
                    
                    (*tmp) = singleRoRight(node->parent);
                    (*tmp)->parent = tmpParent;
                   
                     node = root; 
                }
            }
        }
        else
        {
            RbNode * brother = node->parent->left;
            if(brother->color == RED)
            {
                tmpParent = node->parent->parent;
                if(tmpParent->left == node->parent)
                    tmp = &(tmpParent->left);
                else
                    tmp = &(tmpParent->right);
 
                node->parent->color = RED;
                brother->color = BLACK; 
                (*tmp) = singleRoLeft(node->parent); 
                (*tmp)->parent = tmpParent;
            }
            else
            {
                if(brother->left->color == BLACK && brother->right->color == BLACK)
                {
                    brother->color = RED;
                    node = node->parent;
                }
                else if(brother->right->color == RED && brother->left->color == BLACK)
                {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    node->parent->left = singleRoLeft(brother);
                }
                else if(brother->left->color == RED)
                {
                    tmpParent = node->parent->parent;
                    if(tmpParent->left == node->parent)
                        tmp = &(tmpParent->left);
                    else
                        tmp = &(tmpParent->right); 
                    
                    node->parent->color = BLACK;
                    brother->color = node->parent->color;
                    brother->left->color = BLACK;

                    (*tmp) = singleRoLeft(node->parent);
                    (*tmp)->parent = tmpParent;
                    
                    node = root; 
                }
            }
        }
    }
    root->color = BLACK; 
}

RbTree * RbDelete(int key, RbTree * tree)
{
    RbNode * de_point = find(key, tree->head, tree->NullNode);
    RbNode * NullNode = tree->NullNode;
    RbNode * head = tree->head;

    if(de_point == NULL)
        return NULL;

    if(de_point->left != NullNode && de_point->right != NullNode)
    {
        RbNode * nexter = findMin(de_point->right, NullNode);
        de_point->data = nexter->data;
        de_point = nexter;
    }
    RbNode * de_child;
    if(de_point->left != NullNode)
    {
        de_child = de_point->left;
    }
    else if(de_point->right != NullNode)
    {
        de_child = de_point->right;
    }
    else
        de_child = NullNode;
    
    de_child->parent = de_point->parent; 
    if(de_child->parent == head)
        head->right = de_child;
    else if(de_point->parent->left == de_point)
        de_point->parent->left = de_child;
    else
        de_point->parent->right = de_child;
    
    if(de_point->color != RED && de_child != NullNode)
    {
        DeleteFix(de_child, tree);
    }
    delete de_point;
    return tree;     
} 

#endif
