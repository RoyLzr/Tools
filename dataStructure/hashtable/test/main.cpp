#include "../hashtable.h"

int main()
{
    HashTable<int, int> table(53);
    
    table.insert_unique(0);
    table.insert_unique(6);
    table.insert_unique(7);
    table.insert_unique(8);
    table.PrintHash();
    cout << " test 1" << endl;
    cout << table.find(0)->value << endl;
    table.insert_unique(8);
    table.insert_unique(8);
    cout << "test 2" << endl;
    table.PrintHash();
    table.insert_equal(8);
    table.insert_equal(8);
    cout << "test 3" << endl;
    table.PrintHash();
    
    cout << "test 4" << endl;
    HashTable<char *, char *> table1(53);
    char *value1 = "abcd";
    char *value2 = "abbb";
    char *value3 = "abbc";
    table1.insert_unique(value1);
    table1.insert_unique(value2);
    table1.insert_unique(value3);
    table1.insert_unique(value3);
    table1.PrintHash();
    cout << "test 5" << endl;
    table1.insert_equal(value3);
    table1.PrintHash();
}
