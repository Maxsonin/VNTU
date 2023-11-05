/*Задача 7. Створити файл, що містить відомості  про книги в бібліотеці. Структура запису:
шифр книги, автор, назва, рік видання, місце розташування (номер стелажа, полку).
Передбачити можливість коректування файлу по коду корегування, що вводиться, наприклад:
4 – одержати інформацію про книгу із шифром XXX. 
- Add: Але трохи покращене ;-)*/

// Бібліотеки щоб працювати з потоками і інформацією яку вона містить
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>

struct Book // Інофрмація про книгу
{
    int id;
    std::string firstName;
    std::string lastName;
    std::string title;
    int year;
    int numberOfRoom;
    int numberOfBlock;
    int numberOfShelf;
};

void ParseQuotedString(std::istringstream& ss, std::string& output); // Функція щоб правильно зчитати іформацію з рядка

std::vector<Book> ReadBooksFromFile(const std::string& fileName); // Щоб зчитати інформацію з файлу

// Функції для додавання нової книги
std::string CreateAndAddBook(std::vector<Book>& books);
void AddNewBookToFile(const std::string& fileName, const std::vector<Book>& books, const std::string stringToAdd);

int SeeBook(const std::vector<Book>& books); // функція для показу книги яку обрав користувач та запамятовування його вибору

// Функція для того щоб оновити вже існуючу книгу
void UpdateBook(std::vector<Book>& books, int bookIndexToChenge);
void UpdateBookInFile(const std::string& fileName, const std::vector<Book>& books);

int main()
{
    std::cout << "\tWelcome to Library DataBase!\n";

    std::string fileName = "txtFiles/LibraryBooks.txt";
    std::vector<Book> library = ReadBooksFromFile(fileName);

    int optionIndex = 0;

    while (optionIndex != 3)
    {
        std::cout << "Type option: \n"
            << "1 - If you want to add a new book\n"
            << "2 - If you want to see a book\n"
            << "3 - I want to leave\n";

        std::cout << "Type here: ";
        std::cin >> optionIndex;

        switch (optionIndex)
        {
        case 1:
        {
            std::string stringToAdd = CreateAndAddBook(library);
            AddNewBookToFile(fileName, library, stringToAdd);
            break;
        }
        case 2:
        {
            int BookInSearh = SeeBook(library);
            if (BookInSearh != -1)
            {
                std::cout << "\n\tDo you want to change something in this book?\n"
                    << "1 - Yes, I want to change!\n"
                    << "2 - Just watching...\n";

                std::cout << "Type here: ";
                int userChoice;
                std::cin >> userChoice;
                while (userChoice != 1 && userChoice != 2)
                {
                    std::cout << "Invalid Choice! Try again.\n";
                    std::cin >> userChoice;
                }

                std::cout << "\n\n";

                if (userChoice == 1)
                {
                    UpdateBook(library, BookInSearh);
                    UpdateBookInFile(fileName, library);
                }
            }
            break;
        }
        case 3:
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}

// Реалізації функцій
void ParseQuotedString(std::istringstream& ss, std::string& output)
{
    char c;
    ss >> c;
    output.clear();
    while (ss.get(c) && c != '"')
        output += c;
}

std::vector<Book> ReadBooksFromFile(const std::string& fileName)
{
    std::vector<Book> books;
    std::ifstream fileStream(fileName);

    if (!fileStream.is_open())
    {
        std::cerr << "Error: Unable to open the file.\n";
        return books;
    }

    Book book;

    std::string line;
    while (std::getline(fileStream, line))
    {
        std::istringstream ss(line);
        ss >> book.id;
        ParseQuotedString(ss, book.firstName);
        ParseQuotedString(ss, book.lastName);
        ParseQuotedString(ss, book.title);
        ss >> book.year >> book.numberOfRoom >> book.numberOfBlock >> book.numberOfShelf;
        books.push_back(book);
    }

    return books;
}

void AddNewBookToFile(const std::string& fileName, const std::vector<Book>& books, const std::string stringToAdd)
{
    std::ofstream outFile(fileName, std::ios::app); // Відкриваємо файл для додавання в кінець

    if (!outFile.is_open())
    {
        std::cerr << "Error: Unable to open the file for writing.\n";
        return;
    }

    outFile << '\n' << stringToAdd;

    std::cout << "Nice! Book now on index " << books.back().id << "!\n\n";

    outFile.close();
}

std::string CreateAndAddBook(std::vector<Book>& books)
{
    Book newBook;

    std::cout << "OK! Type New Data:\n";

    newBook.id = books.back().id + 1;

    std::cout << "Author's First Name: ";
    std::cin >> newBook.firstName;

    std::cout << "Author's Last Name: ";
    std::cin >> newBook.lastName;

    std::cout << "Title: ";
    std::cin >> newBook.title;

    std::cout << "Year: ";
    std::cin >> newBook.year;

    std::cout << "Room: ";
    std::cin >> newBook.numberOfRoom;

    std::cout << "Block: ";
    std::cin >> newBook.numberOfBlock;

    std::cout << "Shelf: ";
    std::cin >> newBook.numberOfShelf;

    books.push_back(newBook);

    // Створимо рядок для додавання в файл
    std::string stringToAdd = std::to_string(newBook.id) + " \""
        + newBook.firstName + "\" \""
        + newBook.lastName + "\" \""
        + newBook.title + "\" "
        + std::to_string(newBook.year) + " "
        + std::to_string(newBook.numberOfRoom) + " "
        + std::to_string(newBook.numberOfBlock) + " "
        + std::to_string(newBook.numberOfShelf);

    return stringToAdd;
}

int SeeBook(const std::vector<Book>& books)
{
    std::cout << "\nOk! Type book you want to see:";
    int bookIndexToSearch;
    std::cin >> bookIndexToSearch;

    while (bookIndexToSearch > books.back().id)
    {
        std::cout << "There is no such book! Type another index: ";
        std::cin >> bookIndexToSearch;
    }

    Book book = books[bookIndexToSearch - 1];

    std::cout << "Good! Book Found:\n";

    std::cout << "\t| About Book |\n";
    std::cout << "Index: " << book.id << "\n"
              << "Author: " << book.firstName << " " << book.lastName << "\n"
              << "Title: " << book.title << "\n"
              << "Year: " << book.year << "\n";

    std::cout << "\t| In Library |\n";
    std::cout << "Room: " << book.numberOfRoom << "\n"
              << "Block: " << book.numberOfBlock << "\n"
              << "Shelf: " << book.numberOfShelf << "\n";
    
    return bookIndexToSearch;
}

void UpdateBook(std::vector<Book>& books, int bookIndexToChenge)
{
    std::cout << "Ok! Lets change it!\n";

    std::cout << "Author's First Name: ";
    std::cin >> books[bookIndexToChenge - 1].firstName;

    std::cout << "Author's Last Name: ";
    std::cin >> books[bookIndexToChenge - 1].lastName;

    std::cout << "Title: ";
    std::cin >> books[bookIndexToChenge - 1].title;

    std::cout << "Year: ";
    std::cin >> books[bookIndexToChenge - 1].year;

    std::cout << "Room: ";
    std::cin >> books[bookIndexToChenge - 1].numberOfRoom;

    std::cout << "Block: ";
    std::cin >> books[bookIndexToChenge - 1].numberOfBlock;

    std::cout << "Shelf: ";
    std::cin >> books[bookIndexToChenge - 1].numberOfShelf;

    std::cout << "Nice! Book was successfully updated!\n";

}

void UpdateBookInFile(const std::string& fileName, const std::vector<Book>& books)
{
    std::ofstream outFile(fileName);

    if (!outFile.is_open())
    {
        std::cerr << "Error: Unable to open the file for writing.\n";
        return;
    }

    for (const Book& book : books)
    {
        outFile << book.id << " \"" << book.firstName << "\" \"" << book.lastName << "\" \"" << book.title << "\" "
            << book.year << " " << book.numberOfRoom << " " << book.numberOfBlock << " " << book.numberOfShelf << "\n";
    }

    outFile.close();
}