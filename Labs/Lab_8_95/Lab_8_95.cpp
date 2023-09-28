/*������ 95. ��� ��� �����. ������� ��������, �� �������
����� �� � � ���� ����� � ������� ����� �.*/

#include <iostream>
#include <map>

bool �anConstructWord(const std::string& wordA, const std::string& wordB) //������� ��� �������� �����
{
    std::map<char, int> charCountA;
    std::map<char, int> charCountB;

    // ���������� charCountA �� ������� �� �� ������� � ���� A
    for (char c : wordA)
        charCountA[c]++;

    // ���������� charCountB �� ������� �� �� ������� � ���� B
    for (char c : wordB)
        charCountB[c]++;

    // ����������, �� ����� ������� ����� B �� ���� ����� A
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

    if (�anConstructWord(wordA, wordB))
        std::cout << "Yes, it's possibe!" << std::endl;
    else
        std::cout << "No, it's impossibe!" << std::endl;

    return 0;
}