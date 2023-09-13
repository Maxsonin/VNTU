/*Задача 38.У масиві х(x1, x2, …, xn) знайти найменший елемент
  і вказати його номер. Якщо мінімальних елементів кілька,
  визначити їх кількість. Використати покажчики*/

#include <iostream>
#include <ctime>

void InitializeAndShow(int arr[], int size); // Функція для ініціалізації масиву та виведення його на екран
int FindSmallest(int arr[], int size); // Функція для знаходження найменшого елемента в масиві
void ShowSmallest(int arr[], int size, int smallestNum); // Функція для виведення найменшого елемента в масиві

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // ініціалізує генератор випадкових чисел 

    std::cout << "Enter the size of the array: ";
    int size;
    std::cin >> size;

    int* arr = new int[size]; // створення масиву на кучі
    InitializeAndShow(arr, size);

    int smallestNum = FindSmallest(arr, size);
    ShowSmallest(arr, size, smallestNum);

    delete[] arr; // видаляємо масив з кучі
    return 0;
}

void InitializeAndShow(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10 + 1; // заповнюємо масив випадковими"" числами
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

int FindSmallest(int arr[], int size) // прохидимось по всьому масиву і знаходимо найменший елемент
{
    int smallestNum = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] < smallestNum)
            smallestNum = arr[i];
    }
    return smallestNum;
}

void ShowSmallest(int arr[], int size, int smallestNum)
{
    std::cout << "Smallest number is " << smallestNum << ", and it is at index ";

    for (int i = 0; i < size; i++)
    {
        if (arr[i] == smallestNum)
            std::cout << i << ' ';
    }

    std::cout << std::endl;
}