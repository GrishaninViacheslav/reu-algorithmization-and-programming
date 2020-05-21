// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 11. Определить слова, в которых все буквы повторяются.

#include <iostream>
#include <vector>
#include <cstdio>
int main()
{
    std::string str;
    std::vector<std::string> everyLetterEqualWords;
    while(std::cin >> str)
    {
        for (int i = 1; i < str.size(); i++)
            if (str[i] != str[i-1])
                goto SKIP_THIS_WORD;
        everyLetterEqualWords.push_back(str);
        SKIP_THIS_WORD:
        if (getchar() == '\n')
            break;
    }
    for (auto el : everyLetterEqualWords)
        std::cout << el << " ";
    return 0;
}
