#ifndef _STACK_H_
#define _STACK_H_

#include "LinkedList.h"

struct Stack
{
    List l;
    // void pop();
    // void push(dataOfNode _data);
    // Node *top();
    // bool empty();
    void pop()
    {
        deleteHead(l);
    }
    void push(dataOfNode _data)
    {
        Node *nodeToPush = new Node;
        nodeToPush = createNode(_data);
        addHead(l, nodeToPush);
    }
    Node *top()
    {
        if (l.pHead == NULL)
            return NULL;
        return l.pHead;
    }
    bool empty()
    {
        return l.pHead == NULL;
    }
    void clear()
    {
       while (!empty())
           pop();
    }
};

#endif