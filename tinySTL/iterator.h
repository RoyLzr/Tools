#ifndef __MYITERATOR_H__
#define __MYITERATOR_H__

#include "trait.h"
#include <iostream>

template<class T, class catalog, class ref = T &,
         class point = T *>
class BaseIterator
{
    public:
        typedef T value_type;
        typedef catalog catalog_type;
        typedef ref ref_type;
        typedef point point_type;
};

template<class T, class catalog, class ref = T &,
         class point = T *>
class ArrayIterator : public BaseIterator<T, catalog>
{
    public:
        ArrayIterator() : ptr(NULL){}
        ArrayIterator(T * tmp)
        {
            ptr = tmp;
        }
        ArrayIterator operator+(int n)
        {
            return ArrayIterator(ptr + n);
        }
        ArrayIterator & operator=(T * tmp)
        {
            ptr = tmp;
            return *this;
        }
        ArrayIterator operator-(int n)
        {
            return ArrayIterator(ptr - n);
        }
        bool operator==(const ArrayIterator & i)
        {   return ptr == i.ptr; }
        
        bool operator!=(const ArrayIterator & i)
        {   return ptr != i.ptr; }
        
        //important &
        T & operator*() const 
        {   return *ptr; }
       
        T * operator->() const
        {   return ptr;  } 
   
        T * ptr;
};

template<class T>
class Array
{
    public:

    friend ArrayIterator<T, RandomCatalog>;
    typedef ArrayIterator<T, RandomCatalog> ITER;
    
    ArrayIterator<T, RandomCatalog> iterator;
    ArrayIterator<T, RandomCatalog> ibegin;
    ArrayIterator<T, RandomCatalog> iend;

    Array(int n) : cap(n), size(0)
    {
        T * tmp = new T[n];
        iterator = tmp;
        ibegin = tmp;
        iend = tmp;
    }

    ArrayIterator<T, RandomCatalog> begin()
    {
       return ibegin; 
    }
    
    ArrayIterator<T, RandomCatalog> end()
    {
       return iend; 
    }
    
    void push_back(T value)
    {
        *iend = value;
        iend = iend + 1;    
    }

    private:
    int cap;
    int size;
};

#endif
