/*Написати і протестувати функцію, що перетворить рядок
шістнадцяткових цифр в еквівалентне їй ціле десяткове число.
+Additional Task*/

#include <iostream>

int main()
{
	int x;

	std::cout << "Type '1' to make Hex from Decimal\n"
			  << "Type '2' to make Decimal from Hex\n"
			  << "Choose Type of Conversion: ";

	int userChoice;
	std::cin >> userChoice;
	while (userChoice != 1 && userChoice != 2)
	{
		std::cout << "Invalid choice. Please choose '1' or '2': ";
		std::cin >> userChoice;
	}
	
	// Використовуємо різні маніпулятори для переведення та виведення інформації
	switch (userChoice)
	{
	case 1:
		std::cout << "Type Decimal Number: ";
		std::cin >> x;

		std::cout << "Hexadecimal representation: " << std::hex << std::uppercase << std::showbase << x << std::endl;

		break;
	case 2:
		std::cout << "Type HexaDecimal Number: ";
		std::cin >> std::hex >> x;

		std::cout << "Decimal representation: " << std::dec << x << std::endl;
		break;
	}

	return 0;
}