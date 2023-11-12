/*Задача 90. Створити файл на диску і записати до нього масив чисел.
Прочитати цей файл і вивести його компоненти на екран.
Вивести вміст файлу також і на екран.(-_-)*/

#include <iostream>
#include <fstream>

int* CreateArray(const size_t size);
void UpdateFile(const std::string FileName, const int* arr, const size_t size);

int main()
{
	std::string FileName = "TextFiles/Array.txt";

	size_t size;
	std::cout << "Type array size: ";
	std::cin >> size;
	int* arr = CreateArray(size);
	
	for (size_t i = 0; i < size; i++) std::cout << arr[i] << ' ';

	UpdateFile(FileName, arr, size);

	return 0;
}

int* CreateArray(const size_t size)
{
	srand(time(nullptr));

	int* arr = new int[size];

	for (size_t i = 0; i < size; i++) arr[i] = rand() % 100 + 1;

	return arr;
}

void UpdateFile(const std::string FileName, const int* arr, const size_t size)
{
	std::ofstream outFile(FileName);

	if (!outFile.is_open())
	{
		std::cerr << "Error: Unable to open the file for writing.\n";
		return;
	}

	for (size_t i = 0; i < size; i++) outFile << arr[i] << ' ';

	outFile.close();
}
