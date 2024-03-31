#include "undoButton.h"

void createList(List &l)
{
    l.pHead = new Node;
    l.pHead = NULL;
}
Node *createNode(int **a, int n)
{
    Node *temp = new Node;
    temp->matrix = allocateMatrix(n);
    temp->matrix = a;
    // temp->n = n;
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
        // cout << temp->n << endl;
        printUI(temp->matrix, 4);
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