#ifndef __HANDLE_H__
#define __HANDLE_H__

#include<iostream>
#include<cstdlib>
#include<stdexcept>

template<class T>
class Handle
{
    public:
        Handle(T *p) : ptr(p), use(new size_t(1)) {}
        Handle() : ptr(NULL), use(new size_t(0)) {}
        //copy constuction. add ref
        //tran point 
        Handle(const Handle & h) : ptr(h.ptr), use(h.use)
        {
            (*use)++;
        }
        Handle & operator=(const Handle & h);
        T & operator*();
        T * operator->();
        const T & operator*() const;
        const T * operator->() const;
        ~Handle()
        {
            if(ptr)
            {   rm_ref(); } 
        } 
    private:
        T *ptr;
        size_t *use;
        void rm_ref()
        {
            if(--*use == 0)
            {
                delete ptr;
                delete use;
                ptr = NULL;
                std::cout << "clear one object" << std::endl;
            }
        }
};

template<class T>
inline T & Handle<T>::operator*()
{
    if(ptr)
        return *ptr;
    throw std::runtime_error("not reference");
}

template<class T>
inline T * Handle<T>::operator->()
{
    if(ptr)
        return ptr;
    throw std::runtime_error("not reference");
}

template<class T>
inline Handle<T> & Handle<T>::operator=(const Handle<T> & ref)
{
    //protect assign self
    //why ref can access private use
    ++(*(ref.use));
    rm_ref();
    ptr = ref.ptr;
    use = ref.use;
    return *this;
}

#endif
