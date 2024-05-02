#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "LinkedList.h"

struct Queue
{
    List l;
    // void pop();
    // void push(dataOfNode _data);
    // Node *front();
    // bool empty();
    void pop()
    {
        deleteTail(l);
    }
    void push(dataOfNode _data)
    {
        Node *nodeToPush = new Node;
        nodeToPush = createNode(_data);
        addTail(l, nodeToPush);
    }
    Node *front()
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