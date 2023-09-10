// Завдання 87. Передбачити введення кута а в градусах i переклад його в радiани

#define _USE_MATH_DEFINES // Додає макрос M_PI щоб використовувати Pi
#include <iostream> // cout/cin
#include <cmath> // Додаємо макрови _USE_MATH_DEFINES

int AskUserForChoise(); // Попереднє оголошення функцiй
void DegreesToRadiansFunc();
void RadiansToDegreesFunc();

int main()
{
    AskUserForChoise() == 1 ? DegreesToRadiansFunc() : RadiansToDegreesFunc(); // Тернарний оператор для зменшення обсягу коду в main
    return 0;
}

int AskUserForChoise() // Iмплементацiя функцiї яка дубе повертати вибiр користуача
{
    std::cout << "Choose Type of Conversion:\n"
        << "From Degrees to Radians(press '1')\n"
        << "From Radians to Degrees(press '2')\n";

    int userChoice;
    std::cin >> userChoice;

    if (userChoice != 1 && userChoice != 2) // Якщо користувач введе невiрне число: вивисти повiдомлення про це та запутстити AskUserForChoise() знову
    {
        std::cout << "Invalid Value! Type '1' or '2'\n\n";
        userChoice = 0;
        AskUserForChoise();
    }
    else
    {
        return userChoice;
    }
}

void DegreesToRadiansFunc() // Функцiя перетворення з градусiв в радiани
{
    std::cout << "Type Degrees: ";
    double DegreesVal;
    std::cin >> DegreesVal;

    std::cout << DegreesVal << " Degrees equals " << DegreesVal * M_PI / 180 << " Radians\n";
}


void RadiansToDegreesFunc() // Функцiя перетворення з радiан в градуси
{
    std::cout << "Type Radians: ";
    double RadiansVal;
    std::cin >> RadiansVal;

    std::cout << RadiansVal << " Radians equals " << RadiansVal * 180 / M_PI << " Degrees\n";
}
