// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 12. Определить номера слов, состоящих из тех же символов, что и последнее слово строки.

#include <Windows.h>
#include <iostream>
#include <vector>
#include <set>
#include <string>
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string str;
    std::set<char> lastWordCharsSet;
    std::vector<unsigned> everyCharIsOneOfTheLastWordCharsWordIndexes;  // Вектор номеров слов, состоящих из тех же символов, что и последнее слово строки.
    std::getline(std::cin, str);
    for (std::string::reverse_iterator i = str.rbegin(); i != str.rend(); i++)
    {
        if (*i != ' ')
            lastWordCharsSet.insert(*i);
        if (i != str.rbegin() and *(i - 1) != ' ' and *i == ' ')
            break;
    }
    {
        unsigned currWordIndex = 0;
        bool flag = true; // Ложно если текущее слово не состояит из тех же символов, что и последнее слово строки.
        for (std::string::iterator i = str.begin(), first = str.end(); i != str.end(); i++)
        {
            if (*i != ' ')
            {
                if (lastWordCharsSet.find(*i) == lastWordCharsSet.end())
                    flag = false;
                if(i == str.end() - 1 and flag)
                    everyCharIsOneOfTheLastWordCharsWordIndexes.push_back(currWordIndex);
                if (i == str.begin() or *(i - 1) == ' ')
                {
                    currWordIndex++;
                    first = i;
                }
            }
            else if (i != str.begin() and *(i - 1) != ' ')
            {
                if(flag)
                    everyCharIsOneOfTheLastWordCharsWordIndexes.push_back(currWordIndex);
                flag = true;
            }
        }
    }
    for (auto eciootlwcwIndex : everyCharIsOneOfTheLastWordCharsWordIndexes)
        std::cout << eciootlwcwIndex << " ";
    return 0;
}
