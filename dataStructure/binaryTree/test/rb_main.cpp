#include "../Rbtree.h"

int main()
{
    RbTree *tree = new RbTree();

    tree = RbInsert(10, tree);
    tree = RbInsert(7, tree);
    tree = RbInsert(8, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(15, tree);
    printLevel(level_travel(tree));
    tree = RbInsert(5, tree);
    tree = RbInsert(6, tree);
    printLevel(level_travel(tree));

}
