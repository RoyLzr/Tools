#include "avltree.h"

using namespace std;

int main()
{
    //test rotate
    SearchTree sTree;
    sTree.tree_insert(3, &(sTree.root));
    sTree.tree_insert(5, &(sTree.root));
    sTree.tree_insert(4, &(sTree.root));
    
    sTree.printLevel(sTree.level_travel(sTree.root));
    sTree.root = doubleRoRight(sTree.root);
    cout << endl;
    sTree.printLevel(sTree.level_travel(sTree.root));

    cout << "===============" << endl;

    sTree.root = sTree.clean(sTree.root);
    sTree.tree_insert(5, &(sTree.root));
    sTree.tree_insert(2, &(sTree.root));
    sTree.tree_insert(4, &(sTree.root));
     
    sTree.printLevel(sTree.level_travel(sTree.root));
    sTree.root = doubleRoLeft(sTree.root);
    cout << endl;
    sTree.printLevel(sTree.level_travel(sTree.root));
    
    //test avlTree
    cout << endl;
    cout << "===============" << endl;
    AvlTree aTree;
    for(int i = 0; i < 10; i++)
        aTree.tree_insert(i, &(aTree.root)); 
    aTree.middle_travel(aTree.root);
    aTree.printLevel(aTree.level_travel(aTree.root));
    
    cout << endl;
    cout << "===============" << endl;
    for(int i = 10; i >= 0; i--)
        aTree.tree_insert(i, &(aTree.root)); 
    aTree.printLevel(aTree.level_travel(aTree.root));
 
    return 0;
}
