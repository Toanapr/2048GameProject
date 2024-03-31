#include "undoButton.h"

void createList(List &l)
{
    l.pHead = new Node;
    l.pHead = NULL;
}
Node *createNode(int n)
{
    Node *temp = new Node;
    // temp->matrix = allocateMatrix(n);
    // temp->matrix = a;
    temp->n = n;
    temp->pNext = NULL;
    return temp;
}
void addHead(List &l, Node *nodeAdd)
{
    if (l.pHead == NULL)
    {
        l.pHead = nodeAdd;
        l.pHead->pNext = NULL;
    }
    else
    {
        nodeAdd->pNext = l.pHead;
        l.pHead = nodeAdd;
    }
}
void deleteHead(List &l)
{
    if (l.pHead == NULL)
        return;
    else if (l.pHead->pNext == NULL)
    {
        delete l.pHead;
        l.pHead = NULL;
    }
    else
    {
        Node *temp = l.pHead;
        l.pHead = temp->pNext;
        delete temp;
    }
}
void printList(List &l)
{
    Node *temp = l.pHead;
    if (temp == NULL)
        return;
    while (temp != NULL)
    {
        cout << temp->n << endl;
        temp = temp->pNext;
    }
}
void deleteList(List &l)
{
    if (l.pHead == NULL)
        return;
    else
    {
        while (l.pHead != NULL)
        {
            Node *de = l.pHead;
            l.pHead = l.pHead->pNext;
            delete de;
        }
    }
    delete l.pHead;
}
int main()
{
    List l;
    createList(l);
    Node *a1 = createNode(1);
    Node *a2 = createNode(2);
    Node *a3 = createNode(3);
    addHead(l, a1);
    addHead(l, a2);
    addHead(l, a3);
    printList(l);
    // deleteHead(l);
    // deleteHead(l);
    // deleteHead(l);
    deleteList(l);
    cout << l.pHead;

    // printList(l);
    return 0;
}