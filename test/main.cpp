#include <iostream>
#include<array>

int sum(const int arr[], const int size)
{
    int result = 0;
    for (int i = 0; i < size; ++i)
    {
        result += arr[i];
    }
    return result;
}

int sumP(int* p, int size)
{
    int result = 0;
    for (int i = 0; i < size; ++i)
    {
        result += p[i];
    }
    return result;
}

int sumPA(int* p, int size)
{
    int result = 0;
    for (int i = 0; i < size; ++i)
    {
        result += *(p + i);
    }
    return result;
}

void Reverse(int* p, int size)
{
    int arr[size];

    for (int i = size - 1; i >= 0; --i)
    {
        arr[(size - 1) - i]  = *(p + i);
    }

    for (int i = 0; i < size; ++i)
    {
        p[i] = arr[i];
    }
}

int main()
{
    int arr[] = {1,2,3,4,5,6,7};
    int size = std::end(arr)-std::begin(arr);

    std::cout << sum(arr, size) << std::endl;
    std::cout << sumP(arr, size) << std::endl;
    std::cout << sumPA(arr, size) << std::endl;

    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i];
    }
    std::cout<< std::endl;
    std::cout<< "Reversed: " << std::endl;

    Reverse(arr, size);

    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i];
    }
}
