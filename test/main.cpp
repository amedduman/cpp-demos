#include  <iostream>

int fibonacci(int n)
{
    if(n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int strToInt(char* input)
{
    char* inputStart = input;
    char* inputEnd = nullptr;
    for(; *inputStart != 0; inputStart++)
    {
        inputEnd = inputStart;
    }

    int value = 0;
    int factor = 1;
    for(; inputEnd != input - 1 ;inputEnd--)
    {
        value += (*inputEnd - 48) * factor;
        factor *= 10;
    }

    return value;
}

int main()
{
    char input[3];
    std::cin >> input;
    int n = strToInt(input);
    std::cout << fibonacci(n);
}