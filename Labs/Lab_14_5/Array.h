#pragma once

#include <iostream>
#include <vector>

class Array
{
private:
	size_t size;
    std::vector<int> arr;
public:

    Array(size_t size = 20) : size(size) { std::vector<int> arr(size, 0); }

    void Initialize();
    void Resize(size_t newSize);
    void ShowElements() { for (int number : arr) std::cout << number << ' '; }
    void SeparateEvenAndOdd();
    size_t GetSize() { return size; }

    int& operator[](size_t index) // Overloaded index operator[]
    {
        if (index < size)
            return arr[index];
    }
};

