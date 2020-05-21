// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 10. Определить номер слова-палиндрома, имеющего максимальную длину.

#include <iostream>
#include <cstdio>
int main()
{
    std::string str;
    int maxPalindromeWordIndex = -404;
    for (unsigned maxPalindromeWordLength = 0, currWordLength = 0, currWordIndex = 1; (std::cin >> str); currWordLength = 0, currWordIndex++)
    {
        for (int i = 0; i < str.size() / 2; i++)
            if (str[i] != str[str.size() - 1 - i])
                goto SKIP_THIS_WORD;
        currWordLength = str.size();
        if (currWordLength > maxPalindromeWordLength)
        {
            maxPalindromeWordIndex = currWordIndex;
            maxPalindromeWordLength = currWordLength;
        }
        SKIP_THIS_WORD:
        if (getchar() == '\n')
            break;
    }
    if (maxPalindromeWordIndex != -404)
        std::cout << maxPalindromeWordIndex;
    return 0;
}
