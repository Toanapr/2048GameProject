#include "undoButton.h"

void createList(List &l)
{
    l.pHead = new Node;
    l.pHead = NULL;
}
void copyMatrix(int **a, int **&b, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b[i][j] = a[i][j];
}
Node *createNode(int **a, int n)
{
    Node *temp = new Node;
    temp->matrix = allocateMatrix(n);
    copyMatrix(a, temp->matrix, n);
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
    if (l.pHead->pNext == NULL)
        return;
    else
    {
        Node *temp = l.pHead;
        l.pHead = temp->pNext;
        delete temp;
    }
}
// void printList(List &l)
// {
//     Node *temp = l.pHead;
//     if (temp == NULL)
//         return;
//     while (temp != NULL)
//     {
//         // cout << temp->n << endl;
//         printUI(temp->matrix, 4, 0);
//         temp = temp->pNext;
//     }
// }
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