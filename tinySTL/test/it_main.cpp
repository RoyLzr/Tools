#include "../iterator.h"

using namespace std;

template<class iter>
void output(iter &i)
{
    output(i, catalog_type(i));
}

template<class iter>
void output(iter &i, PerCatalog)
{
    cout << "error not Random" << endl;
}

template<class iter>
void output(iter &i, RandomCatalog)
{
    cout << "good num : " << *i << endl; 
}

template<class T>
void construct(T & i)
{
    construct(i, constr(i));
}

template<class T>
void construct(T & i, FalseType)
{
    cout << "this type do not need construct" << endl;
}

template<class T>
void construct(T & i, TrueType)
{
    cout << "this type need construct" << endl;
}


int main()
{
   Array<int> test1(100);
   for(int i = 0; i < 10; i++)
       test1.push_back(i);
   Array<int>::ITER it = test1.begin();
    
   while(it != test1.end() )
   {
       output(it);
       it = it + 1;
   }   
   ArrayIterator<int, PerCatalog> itPer;
   
   output(itPer);

   char s;
   cout << "char type" << endl; 
   construct(s);   
   
   cout << "array<int> type" << endl; 
   construct(test1);
   
   return 0;
}
