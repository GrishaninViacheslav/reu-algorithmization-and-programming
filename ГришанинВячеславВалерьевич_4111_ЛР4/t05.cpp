// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 5. Поменять местами  i и j слово (номера слов i и j задаются при вводе).

#include <Windows.h>
#include <iostream>
#include <string>
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string str;
    unsigned iWord, jWord;
    std::getline(std::cin, str);
    std::cin >> iWord >> jWord;
    if (iWord > jWord)
    {
        unsigned temp = iWord;
        iWord = jWord;
        jWord = temp;
    }
    if(iWord != jWord)
    {
        unsigned currWordIndex = 1;
        for (std::string::iterator i = str.begin(), iWordBegin = str.end(), iWordEnd = str.end(), jWordBegin = str.end(), jWordEnd = str.end(); i != str.end(); i++)
        {
            if (iWordBegin == str.end() and currWordIndex == iWord)
                iWordBegin = i;
            else if (jWordBegin == str.end() and currWordIndex == jWord)
                jWordBegin = i;
            if (*i != ' ' and (i == str.end() - 1 or *(i + 1) == ' '))
                if (iWordBegin != str.end() and iWordEnd == str.end())
                    iWordEnd = i;
                else if (jWordBegin != str.end() and jWordEnd == str.end())
                    jWordEnd = i;
            if (iWordBegin != str.end() and iWordEnd != str.end() and jWordBegin != str.end() and jWordEnd != str.end())
            {
                iWordEnd++;
                jWordEnd++;
                str = std::string(str.begin(), iWordBegin) + std::string(jWordBegin, jWordEnd) + std::string(iWordEnd, jWordBegin) + std::string(iWordBegin, iWordEnd) + std::string(jWordEnd, str.end());
                break;
            }
            if (i != str.end() - 1 and *i == ' ' and *(i + 1) != ' ')
                currWordIndex++;
        }
    }
    std::cout << str;
    return 0;
}
