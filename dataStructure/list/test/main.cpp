#include "../list.h"

int main()
{
    ListNode * head = new ListNode;
    for(int i = 0; i < 10; i++)
        Insert(head , i);
    Print(head);
    
    cout << "add 10 before 9" << endl;
    InsertBefore(head, 9, 10);
    Print(head);
    
    cout << "add 11 after 9" << endl;
    InsertAfter(head, 9, 11);
    Print(head);

    cout << "delete 10" << endl;
    Delete(head, 10);
    Print(head);

    cout << "delete 0" << endl;
    Delete(head, 0);
    Print(head);
}
