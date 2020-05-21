// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 3. Составить массив из слов, в которых ни одна буква не повторяется.

#include <iostream>
#include <cstdio>
#include <vector>
int main()
{
    std::string str;
    std::vector<std::string> uniqueLettersWords;
    while ((std::cin >> str))
    {
        for (int i = 0; i < str.size(); i++)
            for (int j = 0; j < str.size(); j++)
                if (i != j && str[i] == str[j])
                    goto SKIP_THIS_WORD;
        uniqueLettersWords.push_back(str);
        SKIP_THIS_WORD:
        if (getchar() == '\n')
            break;
    }
    for (auto el : uniqueLettersWords)
        std::cout << el << " ";
    return 0;
}
