#ifndef _STACK_H_
#define _STACK_H_

#include "undoButton.h"

struct stack
{
    List l;
    void pop();
    void push(dataOfNode _data);
    int **top();
    bool empty();
};

#endif 