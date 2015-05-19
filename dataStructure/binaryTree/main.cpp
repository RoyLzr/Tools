#include "tree.h"

int main()
{
    SearchTree tSearch;
    for(int i = 0; i < 10; i++)
    {
        int num = rand() % 100; 
        tSearch.tree_insert(num, &tSearch.root, NULL);
        //tSearch.tree_insert(num, &tSearch.root, NULL);
    }

    tSearch.middle_travel(tSearch.root); 
    std :: cout << "max : " << tSearch.findMax(tSearch.root)->data << std :: endl;
    std :: cout << "min : " << tSearch.findMin(tSearch.root)->data << std :: endl;
    TreeNode * res;
    if((res = tSearch.find(100, tSearch.root) ) == NULL)
        std :: cout << "can not find"<< std :: endl;
    
    tSearch.pathByParent( tSearch.find(21, tSearch.root) );
    
    tSearch.printLevel(tSearch.level_travel(tSearch.root)); 

    tSearch.tree_delete(83, &tSearch.root);
    //tSearch.printLevel(tSearch.level_travel(tSearch.root)); 
    //tSearch.middle_travel(tSearch.root);
    //tSearch.printLevel(tSearch.level_travel(tSearch.root)); 
    cout << " first travel" << endl;
    tSearch.first_travel(tSearch.root);
    cout << " last travel" << endl;
    tSearch.last_travel(tSearch.root);


    return 0;
}
