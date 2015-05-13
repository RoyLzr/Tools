#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <memory>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

//所有同类型的类，共用一段freelist空间
//一次仅支持 一个元素的 new , delete
//freestore 指向下一个可分配空间
//删除时候  1<-2<-3<-4<-5
//free 指向2， 删除4时，更新freestore指向4, 
//4位置的下一个指向2

template<class T>
class CacheObj
{
    public:
        void * operator new(std::size_t);
        void operator delete(void *, std::size_t);
        virtual ~CacheObj(){}
    protected:
        T * next;
    private:
        static const std::size_t chunk = 24;
        static T * freeStore;
        static void add_to_freelist(T *);
        static std::allocator<T> alloc_mem;
};

template<class T>
std::allocator<T> CacheObj<T> :: alloc_mem;

template<class T>
T * CacheObj<T> :: freeStore = 0;

template<class T>
void * CacheObj<T> :: operator new(size_t sz)
{
    if(sz != sizeof(T))
        throw std::runtime_error("size object is error");
    if(!freeStore)
    {
        //分配大量数据
        T * array = alloc_mem.allocate(24);
        std :: cout << "add global memory : " << chunk << std::endl;
        for (size_t i = 0; i != chunk ; i++)
        {
            add_to_freelist(&array[i]);
        } 
    }
    //从global memory中选出一个进行分配
    
    T * p = freeStore;
    freeStore = p->CacheObj<T> :: next;
    return p;
}

//初始化，清空, 对应的global memory 空间
//add global memory
template<class T>
void CacheObj<T> :: add_to_freelist(T * p)
{
    p->CacheObj<T> :: next = freeStore;
    freeStore = p;
}

template<class T>
void CacheObj<T> ::operator delete(void *p, size_t)
{
    if(p != 0)
    {
        add_to_freelist(static_cast<T *> (p) );
    }
}

#endif

