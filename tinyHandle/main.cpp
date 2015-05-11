#include "handle.h"
#include <vector>

class Base
{
    public:
        Base(int n) : val(n) {}
        int val; 
        virtual void out()
        {
            std::cout << "base:"<<val<<std::endl;
        }
};

class Child : public Base
{
    public:
        Child(int n) : Base(n) {}
        virtual void out()
        {
            std::cout << "child" << val << std::endl;
        }
};

int main()
{
    //һ�����ɵĶ���ָ��ֻ�ܽ���һ�� handle�����
    Base *item_test1 = new Base(1);
    Child *item_test2 = new Child(2);

    Handle<Child> test2 = item_test2;
    Handle<Base> test1 = item_test1;
    
    test2->out();
    test1->out();
  
    Handle<Base> test3 = test1;
    Handle<Base> test4;
    test4 = test1; 
    return 0;
}
