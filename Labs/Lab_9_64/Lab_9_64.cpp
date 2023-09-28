/*Варіант 64.
Опишіть, використовуючи структуру шкільний журнал. Передбачте в записі поля для
зберігання інформації про прізвище учня, предмет, оцінку. Складіть програму, що
прочитує з клавіатури дані про успішність учнів класу і що виводить на екран
відомості про відмінників класу, про середню успішність учнів класу.*/

#include <iostream>
#include <vector>
#include <string>

struct Student
{
    std::string studentName;
    int mathScore;
    int ukrainianScore;
    int PEScore;
    int ArtScore;
};

void StudentsProgress(std::vector<Student>& students); // Функція яка показує успішність учнів
void StudentAdd(std::vector<Student>& students, int studentNum); // Функція яка створює список учнів

int main()
{
    std::cout << "Please type how many students do you want to add to your list: ";
    int studentNum;
    std::cin >> studentNum;

    std::cout << std::endl;

    std::vector<Student> studentList(studentNum); // Масив з даними про студентів

    StudentAdd(studentList, studentNum);

    StudentsProgress(studentList);

    return 0;
}

void StudentsProgress(std::vector<Student>& students)
{
    double averageScore;
    double bestScore = 0;
    int bestStudentInd = 0;
    double sumOfAverages = 0;

    for (int i = 0; i < students.size(); i++)
    {
        averageScore = (students[i].mathScore + students[i].ukrainianScore + students[i].PEScore + students[i].ArtScore) / 4.0;
        sumOfAverages += averageScore;

        if (averageScore > bestScore)
        {
            bestStudentInd = i;
            bestScore = averageScore;
        }

        if (averageScore >= 10)
            std::cout << i + 1 << ". " << students[i].studentName << " - has average score " << averageScore << ". He is an excellent student!\n";
        else if (averageScore >= 6 && averageScore <= 9)
            std::cout << i + 1 << ". " << students[i].studentName << " - has average score " << averageScore << ". He is a good student!\n";
        else
            std::cout << i + 1 << ". " << students[i].studentName << " - has average score " << averageScore << ". He is a bad student!\n";
    }

    std::cout << "Best student is " << students[bestStudentInd].studentName << " with average score " << bestScore << std::endl;

    std::cout << "Average class score is " << sumOfAverages / students.size() << std::endl;
}

void StudentAdd(std::vector<Student>& students, int studentNum)
{
    for (int i = 0; i < studentNum; i++)
    {
        std::cout << "Type student at number " << i + 1 << "\n";

        std::cout << "\tType Name: ";
        std::cin.ignore();
        std::getline(std::cin, students[i].studentName);

        std::cout << "\tType Math Score: ";
        std::cin >> students[i].mathScore;

        std::cout << "\tType Ukrainian Score: ";
        std::cin >> students[i].ukrainianScore;

        std::cout << "\tType PE Score: ";
        std::cin >> students[i].PEScore;

        std::cout << "\tType Art Score: ";
        std::cin >> students[i].ArtScore;

        std::cout << "Student " << i + 1 << " Finished!\n\n";
    }

    std::cout << "You have typed all students!" << std::endl;
}

/*
Щоб довго не вписувати ось список з 4 студентів(просто вставити):
4
Maxim Lesko
10
9
11
12
Anton Makron
9
7
3
9
Bodya Boss vsih Pavukiv
12
9
9
11
Loser
1
2
5
3
*/