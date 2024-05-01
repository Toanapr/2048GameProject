#include "2048.h"

void createList(List &l)
{
    l.pHead = new Node;
    l.pHead = NULL;
}
void copyValueMatrix(int **a, int **&b, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            b[i][j] = a[i][j];
}
Node *createNode(dataOfNode _data)
{
    Node *temp = new Node;
    temp->data.score = _data.score;
    temp->data.matrix = allocateMatrix(_data.size);
    copyValueMatrix(_data.matrix, temp->data.matrix, _data.size);
    temp->pNext = NULL;
    return temp;
}
Node *createNode(int **a, int n, int score)
{
    Node *temp = new Node;
    temp->data.matrix = allocateMatrix(n);
    temp->data.score = score;
    copyValueMatrix(a, temp->data.matrix, n);
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
void deleteMatrix(int **&a, int size)
{
    for (int i = 0; i < size; i++)
        delete[] a[i];
    delete a;
    a = NULL;
}
void deleteList(List &l, int size)
{
    if (l.pHead == NULL)
        return;
    else
    {
        while (l.pHead != NULL)
        {
            Node *de = l.pHead;
            deleteMatrix(de->data.matrix, size);
            l.pHead = l.pHead->pNext;
            delete de;
        }
    }
    delete l.pHead;
    l.pHead = NULL;
}
