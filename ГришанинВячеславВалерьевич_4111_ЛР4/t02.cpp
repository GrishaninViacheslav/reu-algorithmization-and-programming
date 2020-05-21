// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 2. Удалить слова с заданным количеством символов.

#include <Windows.h>
#include <iostream>
#include <string>
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string str;
    unsigned num;
    std::getline(std::cin, str);
    std::cin >> num;
    for (std::string::iterator i = str.begin(), first = str.end(); i != str.end(); i++)
    {
        if (*i != ' ')
        {
            if (i == str.end() - 1 and i - first == num - 1)
            {
                str.erase(first, str.end());
                break;
            }
            else if (i == str.begin() or *(i - 1) == ' ')
                first = i;
        }
        else if (i - first == num)
        {
            str.erase(first, i);
            i = first;
        }
    }
    std::cout << str;
    return 0;
}
