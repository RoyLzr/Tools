#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__
#include "tree.h"

TreeNode * constructTwoCore(int *preStart, int *preEnd, int *inStart, int *inEnd);
bool DetectSame(TreeNode * LargeRoot, TreeNode * SmallRoot);
TreeNode * conLastStreeCore(int * start, int * end);
void FindPath(TreeNode * root, int value, int sum, vector<int> &path);
void convertTreeToListCore(TreeNode * root, TreeNode ** pre);
void GetPathOfNode(TreeNode * root, int value1, int value2);

//build tree by preorder and inorder
TreeNode * constructTwoArray(int *preorder, int *inorder, int length)
{
    if(preorder == NULL || inorder == NULL || length ==0)
        return NULL;
    return constructTwoCore(preorder, preorder + length -1, inorder, inorder + length -1);
}

TreeNode * constructTwoCore(int *preStart, int *preEnd, int *inStart, int *inEnd)
{
    TreeNode * root;
    root = new TreeNode(*preStart);
    if(preStart == preEnd)
    {
        if(inStart == inEnd)
            return root;
        else
           std::cout << "invalid tree list" << std::endl; 
    }
    int len = 0; 
    while(*(inStart + len) != root->data)
    {
        if((inStart + len) == inEnd)
            break;
        len ++;
    }

    //when len == 0, no left tree. find value pos is the first number of inorder
    if(len > 0)
    {
        root->leftChild = constructTwoCore(preStart + 1, preStart + len, inStart, inStart + len - 1);
    }
    //when find value pos is last number of inorder, no right tree
    if((inStart + len) < inEnd )
    {
        root->rightChild = constructTwoCore(preStart + len + 1, preEnd, inStart + len + 1, inEnd); 
    }
    return root;
}

//first find head root, then travel child root
bool HasSubTree(TreeNode * LargeRoot, TreeNode * SmallRoot)
{
    bool result = false;
    //preOrder, each find will refresh result. Once result is true, the find travel will stop
    if(LargeRoot != NULL && SmallRoot != NULL)
    {
        if(LargeRoot->data == SmallRoot->data)
            result = DetectSame(LargeRoot, SmallRoot); 
        if(!result)
            result = HasSubTree(LargeRoot->leftChild, SmallRoot);       
        if(!result)
            result = HasSubTree(LargeRoot->rightChild, SmallRoot);       
    }
    return result;
}

bool DetectSame(TreeNode * LargeRoot, TreeNode * SmallRoot)
{
    if(SmallRoot == NULL)
        return true;

    if(LargeRoot == NULL)
        return false;

    if(LargeRoot->data != SmallRoot->data )
        return false;
    
    return  DetectSame(LargeRoot->leftChild, SmallRoot->leftChild) && DetectSame(LargeRoot->rightChild,
                       SmallRoot->rightChild);
}

TreeNode * MirrorBtree(TreeNode * root)
{
    if(root == NULL)
        return NULL;
    TreeNode * tmp = root->leftChild;
    root->leftChild = root->rightChild;
    root->rightChild = tmp;
    
    root->leftChild = MirrorBtree(root->leftChild); 
    root->rightChild = MirrorBtree(root->rightChild);
    return root; 
}

TreeNode * conLastStree(int * list, int len)
{
    if(list == NULL || len <= 0)
        return NULL;
    return conLastStreeCore(list, list + len - 1); 
 
}
TreeNode * conLastStreeCore(int * start, int * end)
{
    TreeNode * root;
    root = new TreeNode(*end);
    int len = 0;

    if(start == end)
        return root;

    while(*(start + len) < root->data)
    {
        if((start + len) == end)
            break;
        len ++;
    }
    
    if(len > 0)
    {
        root->leftChild = conLastStreeCore(start, start + len - 1);
    }
    if(start + len < end)
    {
        root->rightChild = conLastStreeCore(start + len, end - 1);
    }
    return root;
}

//meet invalid value return, else detect next level
bool DetectIsLastBtree(int * start, int length)
{
    if(start == NULL || length < 0)
        return false;
    if(length == 1)
        return true;

    int mid = *(start + length -1);
    int len = 0;
    while(*(start + len) < mid)
    {
        if(len == length - 1)
            break;
        len ++;
    }
    for(int j = len; j < length -1 ; j++)
    {
        //this level get the last result is false, then return.
        //else, go next level to check
        if(start[j] < mid)
            return false;
    }
    bool leftResult = true; 
    if(len > 0)
        leftResult = DetectIsLastBtree(start, len);
    bool rightResult = true;
    if(len < length - 1)
        rightResult = DetectIsLastBtree(start + len, length - 1 - len);
    return (leftResult && rightResult); 
}

void FindPath(TreeNode * root, int value)
{
    if(root == NULL)
        return;
    int sum = 0;
    vector<int> path;
    FindPath(root, value, sum, path);
}

void FindPath(TreeNode * root, int value, int sum, vector<int> &path)
{
    if(root == NULL)
        return;
    path.push_back(root->data);
    sum += root->data;
    if(sum == value && root->leftChild == NULL && root->rightChild == NULL)
    {
        vector<int>::iterator it = path.begin();
        while(it != path.end())
        {
            std::cout << *it << "->" ;
            it++;
        }
        std::cout << std::endl;
    }
    if(root->leftChild != NULL)
        FindPath(root->leftChild, value, sum, path);
    if(root->rightChild != NULL)
        FindPath(root->rightChild, value, sum, path);
    path.pop_back();
}

int GetBtreeHeight(TreeNode * root)
{
    if(root == NULL)
        return 0;
    int lHeight = GetBtreeHeight(root->leftChild); 
    int rHeight = GetBtreeHeight(root->rightChild);
    
    root->height = lHeight > rHeight ? (lHeight + 1) : (rHeight + 1);
    return root->height;
}

bool DetectIsAVLTree(TreeNode * root, int *height)
{
    if(root == NULL)
    {
        *height = 0;
        return true;
    }
    int leftHeight;
    int rightHeight; 
    if(!DetectIsAVLTree(root->leftChild, &leftHeight))
        return false;
    if(!DetectIsAVLTree(root->rightChild, &rightHeight))
        return false;
    
    int diff = leftHeight - rightHeight;
    if(diff > 1 || diff < -1)
        return false;

    *height = (leftHeight > rightHeight) ?(leftHeight + 1):(rightHeight + 1);
    return true;  
}

TreeNode * convertTreeToList(TreeNode * root) 
{
    if(root == NULL)
        return NULL;
    TreeNode * last = NULL;
    convertTreeToListCore(root, &last);
    TreeNode *tmp;
    while(last != NULL)
    {
        std::cout << last->data << std::endl;
        tmp = last;
        last = last->leftChild;
    }
    return tmp; 
}

//mid travel, consider refresh global pre
void convertTreeToListCore(TreeNode * root, TreeNode ** pre)
{
    if(root->leftChild != NULL)
        convertTreeToListCore(root->leftChild, pre);
   
    root->leftChild = *pre;
    if (*pre != NULL)
        (*pre)->rightChild = root;
   
    *pre = root; 
    if(root->rightChild != NULL)
        convertTreeToListCore(root->rightChild, pre);
    return; 
}

vector<int> path1;
vector<int> path2;
vector<int> tmp;
int LowestCommonParent(TreeNode * root, int value1, int value2)
{
    if(root == NULL)
        return -999;
    GetPathOfNode(root, value1, value2);
    vector<int>::iterator it1 = path1.end() - 1;
    vector<int>::iterator it2 = path2.end() - 1;
    if(path1.size() > path2.size())
        it1 = it1 - (path1.size() - path2.size());
    else
        it2 = it2 - (path2.size() - path1.size()); 
    while(it1 >= path1.begin())
    {
        if(*it1 == *it2)
            break;
        it1--;
        it2--;
    }
    if(it1 < path1.begin())
        return -999;
    else
        return *it1; 
}

void GetPathOfNode(TreeNode * root, int value1, int value2)
{
    if(root == NULL)
        return;
    tmp.push_back(root->data);
    if(value1 == root->data)
    {
        path1 = tmp;
    }
    if(value2 == root->data)
    {
        path2 = tmp;
    }
    GetPathOfNode(root->leftChild, value1, value2);
    GetPathOfNode(root->rightChild, value1, value2);
    tmp.pop_back();
    return; 
}

//mid travel operator, consider *k
TreeNode * kthInStree(TreeNode * root, int *k)
{
    if(root == NULL || k == 0)
        return NULL;

    TreeNode * res;
    res = kthInStree(root->leftChild, k);
    if(res != NULL)
        return res;
    (*k)--;
    if(*k == 0)
    {
        return root;
    }
    res = kthInStree(root->rightChild, k);
    return res;
} 

#endif
