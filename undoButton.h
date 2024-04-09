#ifndef _UNDOBUTTON_H_
#define _UNDOBUTTON_H_

#include "2048.h"

struct Node
{
    int **matrix;
    int score;
    // int n;
    Node *pNext;
};
struct List
{
    Node *pHead;
};
void createList(List &l);
Node *createNode(int **a, int n, int score);
void addHead(List &l, Node *nodeAdd);
void deleteHead(List &l);
void deleteList(List &l, int n);
void deleteMatrix(int **&a, int n);
void copyMatrix(int **a, int **&b, int n);

#endif