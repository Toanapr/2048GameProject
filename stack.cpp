#include "stack.h"

void stack::pop()
{
    deleteHead(stack::l);
}
void stack::push(dataOfNode _data)
{
    Node *nodeToPush = new Node;
    copyValueMatrix(_data.matrix, nodeToPush->data.matrix, _data.size);
    nodeToPush->data.score = _data.score;
    nodeToPush->data.size = _data.size;
    addHead(stack::l, nodeToPush);
}
int **stack::top()
{
    if (stack::l.pHead == NULL)
        return NULL;
    return stack::l.pHead->data.matrix;
}
bool stack::empty()
{
    return stack::l.pHead == NULL;
}