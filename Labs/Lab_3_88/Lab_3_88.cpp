//Завдання 88. Перевести задане ціле число в систему римського рахунку.

#include <iostream> // cout/cin
#include <map> // Щоб використовувати std::map<char, int>

int RomanToInt(std::string romanString); // Попереднє оголошення функ. RomanToInt

int main()
{
    std::string s;
    std::cin >> s; // Користувач вводить число Римськими буквами

    std::cout << RomanToInt(s); // Виконання переведення
}

int RomanToInt(std::string romanString) // Імплементація функції
{
    std::map<char, int> values = { {'I', 1}, {'V', 5},{'X', 10},{'L', 50},
                                   {'C', 100},{'D', 500},{'M', 1000} }; // Для зручності використаємо map

    int total = 0; // Загальна сума

    /*Логіка цього for-loop-а полягає в порівнянні current i next значення(
    для прикладу IV: I - менше, а V - більше, тому ми віднімаємо)*/
    for (size_t i = 0; i < romanString.length(); i++)
    {
        if (values[romanString[i]] < values[romanString[i + 1]])
            total -= values[romanString[i]];
        else
            total += values[romanString[i]];
    }
    return total;
}
/*
Можна використати для перевірки:
Example 1:
    Input: s = "III"
    Output: 3
    Explanation: III = 3.

Example 2:
    Input: s = "LVIII"
    Output: 58
    Explanation: L = 50, V= 5, III = 3.

Example 3:
    Input: s = "MCMXCIV"
    Output: 1994
    Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/
