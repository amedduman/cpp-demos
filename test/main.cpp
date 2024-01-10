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

int main()
{
    int arr[] = {1,2,3,4};
    int size = std::end(arr)-std::begin(arr);

    std::cout << sum(arr, size) << std::endl;
    std::cout << sumP(arr, size) << std::endl;
}
