/*Задача 95. Дані два слова. Складіть програму, що визначає
можна чи ні з букв слова А скласти слово В.*/

#include <iostream>
#include <map>

bool ÑanConstructWord(const std::string& wordA, const std::string& wordB) //Функція яка перевіряє умову
{
    std::map<char, int> charCountA;
    std::map<char, int> charCountB;

    // Заповнюємо charCountA із буквами та їх кількістю у слові A
    for (char c : wordA)
        charCountA[c]++;

    // Заповнюємо charCountB із буквами та їх кількістю у слові B
    for (char c : wordB)
        charCountB[c]++;

    // Перевіряємо, чи можна скласти слово B із букв слова A
    for (const auto& pair : charCountB)
    {
        char letter = pair.first;
        int countInB = pair.second;

        if (charCountA[pair.first] < countInB)
            return false;
    }

    return true;
}

int main()
{
    std::cout << "Type word A: ";
    std::string wordA;
    std::cin >> wordA;

    std::cout << "Type word B: ";
    std::string wordB;
    std::cin >> wordB;

    if (ÑanConstructWord(wordA, wordB))
        std::cout << "Yes, it's possibe!" << std::endl;
    else
        std::cout << "No, it's impossibe!" << std::endl;

    return 0;
}
