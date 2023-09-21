/*Написати і протестувати функцію, що перетворить рядок
шістнадцяткових цифр в еквівалентне їй ціле десяткове число.*/

#include <iostream>
#include <iomanip> // Для std::hexfloat щоб маніпулювати формату даних

int main()
{
	float x;

	// Перетворити введене число в десяткове 
	std::cin >> std::hexfloat >> x;
	std::cout << std::fixed << std::setprecision(3) << x << std::endl;

	return 0;
}

/*
* Test cases:
*	9A = 154;
*	45 = 69;
*	B140 = 45376;
*/