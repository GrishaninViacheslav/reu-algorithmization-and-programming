// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 14. Составить массив из слов, в которых все имеющиеся в них цифровые символы образуют монотонную последовательность.

#include <iostream>
#include <vector>
#include <cstdio>
int main()
{
    std::string str;
    std::vector<std::string> digitsFormMonotonicSequenceWords;
    for (char lastDigitChar = 58; (std::cin >> str); lastDigitChar = 58)
    {
        char digitsCountUnder2 = 0;
        char riseDir = 's';
        for (unsigned i = 0; i < str.size(); i++)
            if (str[i] >= 48 and str[i] <= 57)
            {
                if (digitsCountUnder2 < 2)
                    digitsCountUnder2++;

                if (lastDigitChar == 58)
                    lastDigitChar = str[i];
                else if (riseDir == 's')
                {
                    if (str[i] > lastDigitChar)
                        riseDir = 'u';
                    else if (str[i] < lastDigitChar)
                        riseDir = 'd';
                }

                if ((riseDir == 'u' && str[i] < lastDigitChar) || (riseDir == 'd' && str[i] > lastDigitChar))
                    goto SKIP_THIS_WORD;

                lastDigitChar = str[i];
            }
        if (digitsCountUnder2 > 1)
            digitsFormMonotonicSequenceWords.push_back(str);
        SKIP_THIS_WORD:
        if (getchar() == '\n')
            break;
    }
    for (auto el : digitsFormMonotonicSequenceWords)
        std::cout << el << " ";
    return 0;
}
