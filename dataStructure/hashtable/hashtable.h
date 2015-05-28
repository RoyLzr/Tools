#ifndef __HASH__
#define __HASH__

#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <stdlib.h>
#include <string.h>

using namespace std;

template<class T>
class node
{
    public:
        node * next;
        T value;
        node() : next(NULL) {}
        node(T val) : value(val), next(NULL) {} 
};

template<class Key, class Value>
class HashTable
{
    public:
        int Hash(const char *, int tablesize);
        int Hash(int , int tablesize);
        bool equal(const char *, const char *);
        bool equal(int, int);
        typedef node<Value> * Item;

        vector<Item> buckets; 
        HashTable(int tab) : tablesize(tab)
        {
            elements = 0;
            buckets.insert(buckets.begin(), tablesize, (Item) NULL );
        }
        Item find(Key key);
        pair<Item, bool> insert_unique(Key key);
        pair<Item, bool> insert_equal(Key key);
        void PrintHash();
    protected:
        int tablesize;
        int elements; 
};

template<class Key, class Value>
void HashTable<Key, Value> :: PrintHash()
{
    typename vector<Item>::iterator it;
    for(it = buckets.begin(); it != buckets.end(); it++)
    {  
        Item head = (*it);
        while(head != NULL)
        {
            cout << head->value << endl;
            head = head->next;
        }
    }
}

template<class Key, class Value>
bool HashTable<Key, Value> :: equal(const char * s1, const char * s2)
{
    if(strcmp(s1, s2) == 0)
        return true;
    return false;
}

template<class Key, class Value>
bool HashTable<Key, Value> :: equal(int num1, int num2)
{
    if(num1 == num2)
        return true;
    return false;
}
template<class Key, class Value>
pair<node<Value> *, bool> HashTable<Key, Value> :: insert_unique(Key value)
{
    int index = Hash(value, tablesize);
    Item first = buckets[index];
    Item cur;
    for(cur = first; cur != NULL; cur = cur->next)
    {
        if(equal(cur->value, value))
        {
            return pair<Item, bool>(NULL, false);
        }
    }
    Item tmp = new node<Value>(value);
    tmp->next = first;
    buckets[index] = tmp; 
    elements++;
    return pair<Item, bool>(tmp, true);
}


template<class Key, class Value>
pair<node<Value> *, bool> HashTable<Key, Value> :: insert_equal(Key value)
{
    
    int index = Hash(value, tablesize);
    Item first = buckets[index];
    Item cur;
    for(cur = first; cur != NULL; cur = cur->next)
    {
        if(equal(cur->value, value))
        {
            Item tmp = new node<Value>(value);
            tmp->next = cur->next;
            cur->next = tmp;
            elements++;
            return pair<Item, bool>(tmp, true);
        }
    }
    Item tmp = new node<Value>(value);
    tmp->next = first;
    buckets[index] = tmp; 
    elements++;
    return pair<Item, bool>(tmp, true);
}

template<class Key, class Value>
node<Value> * HashTable<Key, Value> :: find(Key key)
{
    int hashval = Hash(key, tablesize);
    Item head = buckets[hashval];
    Item cur = head;
    
    while(cur != NULL && cur->value != key)
        cur = cur->next;
    return cur;
}

template<class Key, class Value>
int HashTable<Key, Value> :: Hash(const char * key, int tablesize)
{
    unsigned int hashval = 0;
    while(*key != '\0')
    {
        hashval += (hashval << 5) + *key;
        key++;
    }
    return hashval % tablesize;
}

template<class Key, class Value>
int HashTable<Key, Value> :: Hash(int key, int tablesize)
{
    return key % tablesize;
}
#endif
