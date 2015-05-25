#ifndef __LIST_H__
#define __LIST_H__
#include <iostream>
#include <stdlib.h>

using namespace std;
class ListNode
{
    public:
        ListNode * next;
        ListNode * pre;
        int data;
        int xishu;
        ListNode() : next(NULL), pre(NULL), 
                     data(0) {}
        ListNode(int value) : next(NULL), 
                              pre(NULL), 
                              data(value) {}
};

bool IsEmpty(ListNode * L)
{
    if(L->next == NULL)
        return true;
    return false;
}

bool IsLast(ListNode * node)
{
    if(node->next == NULL)
        return true;
    return false;
}

ListNode * Find(int value, ListNode * L)
{
    if(IsEmpty(L))
        return NULL;
    ListNode * tmp = L->next;
    while(tmp != NULL && tmp->data != value)
        tmp = tmp->next;
    return tmp;
}

ListNode * FindPre(int value, ListNode * L)
{
    if(IsEmpty(L))
        return NULL;
    ListNode * tmp = L;
    while(tmp->next != NULL && (tmp->next)->data != value)
        tmp = tmp->next;
    if(tmp->next == NULL)
        return NULL;
    return tmp;
}

//insert value after node
void Insert(ListNode * node, int value)
{
    ListNode * added = new ListNode(value);
    if(added == NULL)
        cout << "error new" << endl;    
    added->next = node->next;
    node->next = added; 
    return;
}

void InsertAfter(ListNode * L, int search, int value)
{
    ListNode * tmp = Find(search, L);
    Insert(tmp, value);
}

void InsertBefore(ListNode * L, int search, int value)
{
    ListNode * tmp = FindPre(search, L);
    Insert(tmp, value);
}

void Delete(ListNode * L, int value)
{
    if(IsEmpty(L))
        return;
    ListNode * tmp = FindPre(value, L);
    ListNode * deleted;
    if(tmp != NULL)
    {
        deleted = tmp->next;
        tmp->next = tmp->next->next;
        delete deleted;
    }
    return;
}

void Print(ListNode * L)
{
    while(L != NULL)
    {
        cout << L->data << "->";
        L = L->next;
    } 
    cout << endl;
}


#endif
