#include <iostream>

int AskUserForChoise();
void DegreesToRadiansFunc();
void RadiansToDegreesFunc();

const double PI = 3.141592653589793238462643383279502884197;

int main()
{
    AskUserForChoise() == 1 ? DegreesToRadiansFunc() : RadiansToDegreesFunc();
    return 0;
}

int AskUserForChoise()
{
    std::cout << "Choose Type of Conversion:\n"
        << "From Degrees to Radians(press '1')\n"
        << "From Radians to Degrees(press '2')\n";

    int userChoice;
    std::cin >> userChoice;

    if (userChoice != 1 && userChoice != 2)
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

void DegreesToRadiansFunc()
{
    std::cout << "Type Degrees: ";
    double DegreesVal;
    std::cin >> DegreesVal;

    std::cout << DegreesVal << " Degrees equals " << DegreesVal * PI / 180 << " Radians\n";
}


void RadiansToDegreesFunc()
{
    std::cout << "Type Radians: ";
    double RadiansVal;
    std::cin >> RadiansVal;

    std::cout << RadiansVal << " Radians equals " << RadiansVal * 180 / PI << " Degrees\n";
}
