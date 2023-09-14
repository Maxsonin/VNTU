#include <iostream>
#include <string>

int main()
{
	std::cout << "Enter string to chack: ";
	std::string s;
	std::cin >> s;

	bool IsAlphabetic = true; 

	for (int i = 0; i < s.length() - 1; i++)
	{
		if (tolower(s[i]) + 1 != tolower(s[i + 1])) /*Якщо число UNICODE currant елемента НЕ
												      дорівнює наступному числу UNICODE + 1 
													  то це не алфавітний порядок (A = 65, B = 66)*/
		{
			IsAlphabetic = false;
			break;
		}
	}

	if (IsAlphabetic == false)
		std::cout << "String in NOT in alphabetical sequence";
	else
		std::cout << "String in alphabetical sequence";

	return 0;
}