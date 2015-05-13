#include "cacheObj.h"
#include <string>

class Test : public CacheObj<Test>
{
    public:
        Test(int n) : val(n) {}
        int getVal() const
        {   return val;   }
    private:
        int val;
};

int main()
{
    for(int i = 0; i < 240; i++)
    { 
        Test * p = new Test(1);
    }
    
    std :: cout << "mark" << std::endl;
    for(int i = 0; i < 240; i++)
    { 
        Test * p1 = new Test(1);
        Test * p2 = new Test(1);
        delete p1;
        delete p2;
    }
    
    std :: cout << "mark" << std::endl;
    for(int i = 0; i < 240; i++)
    { 
        Test * p1 = new Test(1);
        Test * p2 = new Test(1);
        delete p1;
    }
   
   
    return 0;
}
