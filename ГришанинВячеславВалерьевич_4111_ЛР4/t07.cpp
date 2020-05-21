// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 7. Определить слово максимальной длины, в котором все символы различны.

#include <iostream>
#include <cstdio>
int main()
{
    std::string str,
                maxUniqueLettersWord;
    for(unsigned maxUniqueLettersWordLength = 0, currWordLength = 0; (std::cin >> str); currWordLength = 0)
    {
        for (int i = 0; i < str.size(); i++, currWordLength++)
            for (int j = 0; j < str.size(); j++)
                if (i != j && str[i] == str[j])
                    goto SKIP_THIS_WORD;
        if(currWordLength > maxUniqueLettersWordLength)
        {
          maxUniqueLettersWord = str;
          maxUniqueLettersWordLength = currWordLength;
        }
        SKIP_THIS_WORD:
        if (getchar() == '\n')
            break;
    }
    if(maxUniqueLettersWord.size())
      std::cout << maxUniqueLettersWord;
    return 0;
}
