#include <iostream>
#include "stack.h"

int main()
{
    Stack s;

    s.Push(1);
    s.Push(2);
    s.Pop();
    s.Push(2);
    s.Push(3);
    s.Push(4);

    // s.Print();

    Stack s2 = s;

    s2.Print();
}
