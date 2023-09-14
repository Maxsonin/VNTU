#include <iostream>
#include <string>

bool IsAlphabetic(std::string string);
std::string AskAndChackIsDigit();

int main()
{
	std::string s = AskAndChackIsDigit();

	if (IsAlphabetic(s))
		std::cout << "String in alphabetical sequence";
	else
		std::cout << "String in NOT in alphabetical sequence";

	return 0;
}

bool IsAlphabetic(std::string string)
{
	/*Якщо число UNICODE currant елемента НЕ дорівнює
	  наступному числу UNICODE + 1 то це не алфавітний
	  порядок (A = 65, B = 66)*/
	for (int i = 0; i < string.length() - 1; i++)
	{
		if (tolower(string[i]) + 1 != tolower(string[i + 1]))
		{
			return false;
		}
	}
	return true;
}

std::string AskAndChackIsDigit()
{
	std::cout << "Enter string to chack: ";
	std::string s;
	std::cin >> s;
			
	for (char c : s)
	{
		if (std::isdigit(c))
		{
			std::cout << "Type String WITHOUT Numbers\n";
			s.clear();
			return AskAndChackIsDigit();
			/*Рекурсивно викликаємо функцію
			AskAndChackIsDigit до того моменту
			поки користувач не введе string без чисел*/
		}
	}
	return s;
}