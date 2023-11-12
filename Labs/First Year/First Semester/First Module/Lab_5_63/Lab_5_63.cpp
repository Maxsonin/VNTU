// Задача 63. Знайдіть суму елементів s із заштрихованої області(2 діангоналі)

#include <iostream>

void Initialize(int arr[][9]); // Функція для ініціалізації масиву
void Show(int arr[][9]); // Функція для виведення масиву
int SumOfDiagonals(int arr[][9]); // Функція для знаходження суми

int main()
{
	int arr[9][9];
	Initialize(arr);
	Show(arr); // Створення -> Ініціалізація -> Виведення на екран

	std::cout << "Sum of Diagonals: " << SumOfDiagonals(arr) << std::endl;

	return 0;
}

void Initialize(int arr[][9])
{
	srand(static_cast<unsigned>(time(nullptr))); // ініціалізує генератор випадкових чисел 

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			arr[i][j] = rand() % 9 + 1;
}

void Show(int arr[][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			std::cout << arr[i][j] << ' ';

		std::cout << std::endl;
	}
}

int SumOfDiagonals(int arr[][9])
{
	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		sum += arr[i][i]; // Сума голонвої діагоналі
		sum += arr[i][8 - i]; // Сума іншої діагоналі
	}

	return sum;
}