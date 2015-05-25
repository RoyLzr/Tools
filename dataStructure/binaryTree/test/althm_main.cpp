#include "../tree.h"
#include "../algorithm.h"
#include "../avltree.h"

using namespace std;

int main()
{
    //test preorder inorder rebuild
    int pre[] = {1,2,4,7,3,5,6,8};
    int in[] =  {4,7,2,1,5,3,8,6};
    TreeNode *tree = constructTwoArray(pre, in, sizeof(pre)/sizeof(int));
    SearchTree sTree;
    sTree.printLevel(sTree.level_travel(tree));

    //test find sub tree
    cout << endl << "another sub exist test" << endl;
    SearchTree sTree1;
    sTree1.tree_insert(5, &(sTree1.root));
    sTree1.tree_insert(6, &(sTree1.root));
    sTree1.tree_insert(4, &(sTree1.root));
    sTree1.tree_insert(2, &(sTree1.root));
    sTree1.tree_insert(1, &(sTree1.root));
    sTree1.tree_insert(3, &(sTree1.root));
    
    SearchTree sub1;
    sub1.tree_insert(5, &(sub1.root));
    sub1.tree_insert(4, &(sub1.root));
    sub1.tree_insert(6, &(sub1.root));
    if (HasSubTree(sTree1.root, sub1.root))
        cout << "yes" << endl;

    sTree1.tree_delete(6, &(sTree1.root));

    cout << HasSubTree(sTree1.root, sub1.root) << endl; 
    sub1.clean(sub1.root);
    sub1.tree_insert(2, &(sub1.root));
    sub1.tree_insert(3, &(sub1.root));
    cout << HasSubTree(sTree1.root, sub1.root) << endl; 
    
    //test mirror tree
    cout << endl << "another mirror test" << endl;
    sTree.printLevel(sTree.level_travel(sTree1.root));
    cout << endl;
    sTree1.root = MirrorBtree(sTree1.root);
    sTree.printLevel(sTree.level_travel(sTree1.root));
    
    //test construct last order Stree
    cout << endl << "another lastorder test" << endl;
    int last[] = {1,3,2,4,5};
    TreeNode * lastRoot = conLastStree(last, sizeof(last)/sizeof(int)); 
    cout << endl;
    sTree.printLevel(sTree.level_travel(lastRoot));
    
    //test sequence is last order Stree 
    cout << endl << "another sequence is last order Stree test" << endl;
    cout << endl;
    cout << DetectIsLastBtree(last, sizeof(last)/sizeof(int)) << endl;
    cout << DetectIsLastBtree(in, sizeof(in)/sizeof(int)) << endl;
    int tOrder[] = {1};
    cout << DetectIsLastBtree(tOrder, sizeof(tOrder)/sizeof(int)) << endl;
    
    //test sum path 
    cout << endl << "another sum path test" << endl;
    sTree.printLevel(sTree.level_travel(tree));
    FindPath(tree, 9);    
    FindPath(tree, 14);    
    
    //test get height   
    cout << endl << "another tree height test" << endl;
    sTree.printLevel(sTree.level_travel(lastRoot));
    GetBtreeHeight(lastRoot);
    cout << sTree.findMin(lastRoot)->height << endl; 
    cout << sTree.find(5, lastRoot)->height << endl; 

    //test is AVL TREE    
    cout << endl << "another avl tree test" << endl;
    AvlTree aTree;
    for(int i = 0; i < 3; i++)
        aTree.tree_insert(i, &(aTree.root)); 
    sTree.printLevel(sTree.level_travel(aTree.root));
    int avlheight;
    cout << endl << DetectIsAVLTree(aTree.root, &avlheight);
    avlheight = 0;
    cout << endl << DetectIsAVLTree(sTree.root, &avlheight);
    avlheight = 0;
    cout << endl << DetectIsAVLTree(lastRoot, &avlheight);

    //test is AVL TREE    
    cout << endl << "another avl tree test" << endl;
    TreeNode * testList = convertTreeToList(aTree.root);        
    while(testList != NULL)
    {   
        cout << testList->data << endl;
        testList = testList->rightChild;
    }
    cout << endl;  
    
    //lowest common root
    cout << endl << "another lowest common root" << endl;
    sTree.printLevel(sTree.level_travel(tree));
    cout << endl << endl << LowestCommonParent(tree, 2, 3) << endl;
    cout << endl << endl << LowestCommonParent(tree, 7, 8) << endl;
    cout << endl << endl << LowestCommonParent(tree, 8, 5) << endl;
    
    //kth point of Search Tree
    cout << endl << "another kth point of Search Tree" << endl;
    sTree1.root = MirrorBtree(sTree1.root);
    sTree.printLevel(sTree.level_travel(sTree1.root));
    int tmp = 1;
    cout << endl << kthInStree(sTree1.root, &tmp)->data << endl;
    tmp = 2;
    cout << endl << kthInStree(sTree1.root, &tmp)->data << endl;
    tmp = 5;
    cout << endl << kthInStree(sTree1.root, &tmp)->data << endl;
   
     
    return 0;
}
