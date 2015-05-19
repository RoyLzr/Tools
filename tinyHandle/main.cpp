#include "handle.h"
#include <vector>

class Base
{
    public:
        Base(int n) : val(n) {}
        int val;
        explicit Base(const Base &){}; 
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

void out(Base tt)
{
    std::cout << tt.val << std::endl;
}

int main()
{
    //一个生成的对象指针只能交给一个 handle类管理
    
    Base *item_test1 = new Base(1);
    Child *item_test2 = new Child(2);

    Handle<Child> test2 = item_test2;
    Handle<Base> test1 = item_test1;
    
    test2->out();
    //转意 test1->ptr->out()
    test1->out();
  
    Handle<Base> test3 = test1;
    Handle<Base> test4;
    test4 = test1;
    
    //test explicit
    Base base1(1);

    //error explicit Base
    //explicit = 初始化 不能运行 同理函数参数传递时候调用的
    //拷贝构造函数为explicit 不能进行转化。所以函数此处调用
    //也是错误
    //Base base2 = base1;
    //out(base1);
    
    return 0;
}
