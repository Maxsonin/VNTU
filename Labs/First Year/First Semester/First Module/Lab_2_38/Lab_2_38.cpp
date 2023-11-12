/*Завдання 38. Вiдомо, що астрологи поділяють рік на 12 періодів і кожному
з них ставлять у відповідність один  зі  знаків  Зодіаку:
20.1 – 18.2 - Водолій      23.7  – 22.8  - Лев
19.2 – 20.3 - Риби         23.8  - 22.9  - Діва
21.3 – 19.4 - Овна         23.9  - 22.10 - Ваги
20.4 – 20.5 - Телець       23.10 – 22.11 - Скорпіон
21.5 – 21.6 - Близнюки     23.11 - 21.12 - Стрілець
22.6 – 22.7 - Рак          22.12 - 19.1  - Козоріг
Написати програму, що вводить дату деякого дня року і друкує назву відповідного знака Зодіаку.*/

#include <iostream> //Щоб використовувати cout/cin

std::string ZodiacSignFinder(int month, int day); //Попереднє оголошення функції ZodiacSignFinder

int main()
{
    int month, day; //створення двох змінних, для того щоб зберігати дані які введе користувач

    std::cout << "Type Month(1-12): ";
    std::cin >> month;

    std::cout << "Type Day(1-31): ";
    std::cin >> day;

    std::cout << "Your Zodiac Sign: " << ZodiacSignFinder(month, day) << std::endl; //Вивід результуту

    return 0;
}

std::string ZodiacSignFinder(int month, int day) // Iмплементація функції ZodiacSignFinder
{
    if ((month == 3 && day >= 21) || (month == 4 && day <= 20)) return "Aries(Oven)";
    else if ((month == 4 && day >= 21) || (month == 5 && day <= 21)) return "Taurus(Telets')";
    else if ((month == 5 && day >= 22) || (month == 6 && day <= 21)) return "Gemini(Blyznyuky)";
    else if ((month == 6 && day >= 22) || (month == 7 && day <= 22)) return "Cancer(Rak)";
    else if ((month == 7 && day >= 23) || (month == 8 && day <= 22)) return "Leo(Lev)";
    else if ((month == 8 && day >= 23) || (month == 9 && day <= 23)) return "Virgo(Diva)";
    else if ((month == 9 && day >= 24) || (month == 10 && day <= 23)) return "Libra(Terezy)";
    else if ((month == 10 && day >= 24) || (month == 11 && day <= 21)) return "Scorpio(Scorpion)";
    else if ((month == 11 && day >= 22) || (month == 12 && day <= 21)) return "Sagittarius(Strilets')";
    else if ((month == 12 && day >= 22) || (month == 1 && day <= 21)) return "Capricorn(Kozorih)";
    else if ((month == 1 && day >= 21) || (month == 2 && day <= 18)) return "Aquarius(Vodoliy)";
    else return "Pisces(Riby)";
}
// Iдея функцiї полягає в порiвняннi дня та мiсяцi з тим днем та мiсяцем якому цей знак зодiаку належить