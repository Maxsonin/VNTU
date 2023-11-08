// 5.  Непарні елементи масиву  М(20) записати в масив М1, а парні – в масив  M2.(-_-)
#include "Array.h"

void SetSeedForRandomNums() { srand(time(nullptr)); }

int main()
{
	SetSeedForRandomNums();

	Array arr(10);
	arr.Initialize();
	std::cout << "Origanal Array: ";
	arr.ShowElements();
	std::cout << "\n";
	arr.SeparateEvenAndOdd();
	//
	std::cout << "\n";
	//
	arr.Resize(11);
	std::cout << "Resized Array:  ";
	arr.ShowElements();
	std::cout << "\n";
	arr.SeparateEvenAndOdd();
	//
	std::cout << "\n";
	//
	arr.Resize(20);
	arr.Initialize();
	std::cout << "Resized Array2: ";
	arr.ShowElements();
	std::cout << "\n";

	return 0;
}