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
    return mid;
}


RbNode * singleRoRight(RbNode * node)
{
    if(node == NULL)
        return NULL;

    RbNode * mid = node->right;
    node->right = mid->left;
    mid->left = node;
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
            cout << tmp.first->data << "("<<tmp.first->color<<")"  <<" ";
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


#endif
