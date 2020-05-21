// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 4. Составить массив из номеров слов , в которых есть повторяющиеся символы.

#include <iostream>
#include <cstdio>
#include <vector>
int main()
{
    std::string str;
    std::vector<int> uniqueLettersWords;
    for(unsigned currWordIndex = 1; (std::cin >> str); currWordIndex++)
    {
        for (int i = 0; i < str.size(); i++)
            for (int j = 0; j < str.size(); j++)
                if (i != j && str[i] == str[j])
                {
                    uniqueLettersWords.push_back(currWordIndex);
                    goto SKIP_THIS_WORD;
                }
        SKIP_THIS_WORD:
        if (getchar() == '\n')
            break;
    }
    for (auto el : uniqueLettersWords)
        std::cout << el << " ";
    return 0;
}
