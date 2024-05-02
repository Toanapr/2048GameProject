#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "2048.h"

struct dataOfNode
{
    int **matrix;
    int score;
    int size;
};
struct Node
{
    dataOfNode data;
    Node *pNext;
};
struct List
{
    Node *pHead;
    List()
    {
        pHead = NULL;
    }
};
void createList(List &l);
Node *createNode(dataOfNode data);
void addHead(List &l, Node *nodeAdd);
void addTail(List &l, Node *nodeAdd);
void deleteHead(List &l);
void deleteTail(List &l);
void deleteList(List &l, int n);
void deleteMatrix(int **&a, int n);
void copyValueMatrix(int **a, int **&b, int n);

#endif