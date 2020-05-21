// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 6. Поменять местами слово максимальной и слово минимальной длины.

// В задании не определенно какие слова менять местами в том лучае если в строке есть
// несколь слов с наибольшей или наименьшей длинной. Предположим, что под словом с
// максимальной длиной подразумевалось первое слово в строке  с наибольшей длиной, а под
// словом с минимальной длиной подразумевалось первое слово в строке с наименьшей длиной.

#include <Windows.h>
#include <iostream>
#include <string>
void swapIWordAndJWordInStr(std::string&, unsigned, unsigned);
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string str;
    unsigned minLengthWordIndex, minLengthWordSize = INT_MIN+INT_MAX,
             maxLengthWordIndex, maxLengthWordSize = 0;
    std::getline(std::cin, str);
    {
      unsigned currWordIndex = 0;
      for (std::string::iterator i = str.begin(), first = str.end(); i < str.end(); i++)
      {
          if (*i != ' ')
          {
              if (i == str.end() - 1 and (i - first < minLengthWordSize - 1 or i - first > maxLengthWordSize - 1))
              {
                  i++;
                  goto UPDATE_MINMAX_LENGTHWORD;
              }
              else if (i == str.begin() or *(i - 1) == ' ')
              {
                currWordIndex++;
                first = i;
              }

          }
          else if(i != str.begin() and *(i-1) != ' ')
          {
              UPDATE_MINMAX_LENGTHWORD:
              if (i - first < minLengthWordSize)
              {
                  minLengthWordIndex = currWordIndex;
                  minLengthWordSize = i - first;
              }
              else if (i - first > maxLengthWordSize)
              {
                  maxLengthWordIndex = currWordIndex;
                  maxLengthWordSize = i - first;
              }
          }
      }
    }
    swapIWordAndJWordInStr(str, minLengthWordIndex, maxLengthWordIndex);
    std::cout << str;
    return 0;
}
void swapIWordAndJWordInStr(std::string& str, unsigned iWord, unsigned jWord)
{
    if (iWord > jWord)
    {
        unsigned temp = iWord;
        iWord = jWord;
        jWord = temp;
    }
    if (iWord != jWord)
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
}
