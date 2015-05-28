#include "../Rbtree.h"

int main()
{
    RbTree *tree = new RbTree();

    tree = RbInsert(10, tree);
    tree = RbInsert(7, tree);
    //tree = RbDelete(10, tree);
    tree = RbInsert(8, tree);
    //printLevel(level_travel(tree));
    tree = RbInsert(15, tree);
    //printLevel(level_travel(tree));
    tree = RbInsert(5, tree);
    tree = RbInsert(6, tree);
    
    tree = RbInsert(1, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(2, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(3, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(4, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(9, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(0, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(-1, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(-2, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(-3, tree);
    printLevel(level_travel(tree));
    
     
    printLevel(level_travel(tree));
    
    tree = RbDelete(0, tree); 
    printLevel(level_travel(tree));
    tree = RbDelete(5, tree); 
    printLevel(level_travel(tree));
    tree = RbDelete(6, tree);
    printLevel(level_travel(tree));
    tree = RbDelete(15, tree); 
    printLevel(level_travel(tree));
    cout << "==========7========" << endl;
    tree = RbDelete(7, tree); 
    printLevel(level_travel(tree));
    
    cout << endl << "10" << endl;
    tree = RbDelete(10, tree); 
    printLevel(level_travel(tree));
    tree = RbDelete(9, tree); 
    printLevel(level_travel(tree));
    tree = RbDelete(3, tree); 
    printLevel(level_travel(tree));
    tree = RbDelete(-1, tree); 
    printLevel(level_travel(tree));
    tree = RbDelete(4, tree); 
    tree = RbDelete(2, tree); 
    tree = RbDelete(1, tree); 
    tree = RbDelete(8, tree); 
    tree = RbDelete(-2, tree); 
    printLevel(level_travel(tree));
    
    //for(int i = 100; i < 200; i++)
    //    tree = RbInsert(i, tree);
    
    //tree = RbDelete(100, tree);
    //for(int i = 100; i < 200; i++)
    //{
    //    tree = RbDelete(i, tree);
    //    cout << "end : " << i << endl; 
    //}
    
    //printLevel(level_travel(tree));
}
