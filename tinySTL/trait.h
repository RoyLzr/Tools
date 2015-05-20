#ifndef __TRAIT_H__
#define __TRAIT_H__

struct PerCatalog {}; 
struct RandomCatalog : public PerCatalog{}; 
struct TrueType {};
struct FalseType {};

//iterator_trait, template is iterator or point
template<class I>
class iterator_trait
{
    public:
    typedef typename I::value_type value_type;
    typedef typename I::catalog_type catalog_type;
    typedef typename I::ref_type ref_type;
    typedef typename I::point_type point_type;
};

//int *, char * is random
template<class I>
class iterator_trait<I *>
{
    public:
    typedef I value_type;
    typedef RandomCatalog catalog_type;
    typedef I & ref_type;
    typedef I * point_type;
};

template<class I>
class iterator_trait<const I *>
{
    public:
    typedef I value_type;
    typedef RandomCatalog catalog_type;
    typedef I & ref_type;
    typedef I * point_type;
};

//return point
template<class I>
inline typename iterator_trait<I>::value_type * 
value_type(const I &)
{
    return static_cast<typename iterator_trait<I>::value_type *>(0);
}

//return point
template<class I>
inline typename iterator_trait<I>::catalog_type 
catalog_type(const I &)
{
    typedef typename iterator_trait<I>::catalog_type catalog;
    return catalog();
}

template<class T>
class type_trait
{
    public:
    typedef TrueType has_construct; 
    typedef TrueType has_destroy; 
};

template<>
class type_trait<char>
{
    public:
    typedef FalseType has_construct; 
    typedef FalseType has_destroy; 
};

template<>
class type_trait<int>
{
    public:
    typedef FalseType has_construct; 
    typedef FalseType has_destroy; 
};

template<class T>
inline typename type_trait<T>::has_construct
constr(const T &)
{
    typedef typename type_trait<T>::has_construct con;
    return con();
}

#endif
