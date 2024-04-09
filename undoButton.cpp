#include "2048.h"

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
Node *createNode(int **a, int n, int score)
{
    Node *temp = new Node;
    temp->matrix = allocateMatrix(n);
    temp->score = score;
    copyMatrix(a, temp->matrix, n);
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
    Node *temp = l.pHead;
    l.pHead = l.pHead->pNext;
    delete temp;
}
void deleteMatrix(int **&a, int n)
{
    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete a;
    a = NULL;
}
void deleteList(List &l, int n)
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
    l.pHead = NULL;
}
