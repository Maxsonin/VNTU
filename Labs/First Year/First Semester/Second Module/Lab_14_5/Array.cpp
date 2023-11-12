// In this file we have implementations of functions

#include "Array.h"

void Array::Initialize()
{
    if (arr.empty())
        for (size_t i = 0; i < size; i++)
            arr.push_back(rand() % 10 + 1);
    else
        for (int& number : arr)
            number = rand() % 10 + 1;
}

void Array::Resize(size_t newSize)
{
    int oldSize = GetSize();

    if (newSize > 0)
    {
        size = newSize;
        arr.resize(newSize);
    }

    for (size_t i = oldSize; i < newSize; i++) arr[i] = rand() % 10 + 1;
}

void Array::SeparateEvenAndOdd()
{
    int sizeOfSubArrays = GetSize() / 2;

    // if we have odd size of main array, we will always
    // have odd subarray size bigger, than size of even subarray
    Array arrEven(sizeOfSubArrays);
    Array arrOdd(GetSize() % 2 != 0 ? sizeOfSubArrays + 1 : sizeOfSubArrays);

    for (size_t i = 0; i < GetSize(); i++)
        i % 2 == 0 ? arrEven.arr.push_back((*this)[i]) : arrOdd.arr.push_back((*this)[i]);

    std::cout << "Odd:  ";
    arrOdd.ShowElements();
    std::cout << "\nEven: ";
    arrEven.ShowElements();
    std::cout << '\n';
}