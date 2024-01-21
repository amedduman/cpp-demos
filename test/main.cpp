#include <iostream>
#include "Stack.h"

int main()
{
    using namespace std;

    Stack s;
    s.Push( 1 );
    s.Push( 2 );
    s.Push( 3 );
    s.Push( 4 );

    s.Print();

    // multiply all elements by 10
    for( auto& n : s )
    {
        *n *= 10;
    }

    cout << "after mul " << endl;

    s.Print();
}