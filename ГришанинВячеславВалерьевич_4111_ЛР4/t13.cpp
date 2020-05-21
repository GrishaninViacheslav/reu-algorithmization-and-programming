// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 13. Определить количество слов, в которых все имеющиеся в них цифровые символы упорядочены по невозрастанию.

#include <iostream>
#include <cstdio>
int main()
{
    std::string str;
    unsigned counter = 0; // Количество слов, в которых все имеющиеся в них цифровые символы упорядочены по невозрастанию.
    for (char lastDigitChar = 58; (std::cin >> str); lastDigitChar = 58)
    {
        char digitsCountUnder2 = 0;
        for (unsigned i = 0; i < str.size(); i++)
            if (str[i] >= 48 and str[i] <= 57)
            {
                if (digitsCountUnder2 < 2)
                    digitsCountUnder2++;
                if (str[i] > lastDigitChar)
                    goto SKIP_THIS_WORD;
                lastDigitChar = str[i];
            }
        if (digitsCountUnder2 > 1)
            counter++;
        SKIP_THIS_WORD:
        if (getchar() == '\n')
            break;
    }
    std::cout << counter;
    return 0;
}
