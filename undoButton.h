#include "2048.h"

struct Node
{
    int **matrix;
    // int n;
    Node *pNext;
};
struct List
{
    Node *pHead;
};
void createList(List &l);
Node *createNode(int **a, int n);
void addHead(List &l, Node *nodeAdd);
void deleteHead(List &l);
void printList(List &l);
void deleteList(List &l);
