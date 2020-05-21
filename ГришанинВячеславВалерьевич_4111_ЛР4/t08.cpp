// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 8. Определить слова, в которых содержится больше двух гласных букв русского алфавита.

#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string str;
    std::set<char> cyrillicVowelsSet;
    std::vector<std::string> wordsWithMoreThan2CrillicVowels;
    cyrillicVowelsSet.insert('а'); cyrillicVowelsSet.insert('А');
    cyrillicVowelsSet.insert('и'); cyrillicVowelsSet.insert('И');
    cyrillicVowelsSet.insert('е'); cyrillicVowelsSet.insert('Е');
    cyrillicVowelsSet.insert('е'); cyrillicVowelsSet.insert('Е');
    cyrillicVowelsSet.insert('о'); cyrillicVowelsSet.insert('О');
    cyrillicVowelsSet.insert('у'); cyrillicVowelsSet.insert('У');
    cyrillicVowelsSet.insert('ы'); cyrillicVowelsSet.insert('Ы');
    cyrillicVowelsSet.insert('э'); cyrillicVowelsSet.insert('Э');
    cyrillicVowelsSet.insert('ю'); cyrillicVowelsSet.insert('Ю');
    cyrillicVowelsSet.insert('я'); cyrillicVowelsSet.insert('Я');
    for(unsigned cVowelCount = 0; (std::cin >> str); cVowelCount = 0)
    {
        for (unsigned i = 0; i < str.size(); i++)
        {
            if (cyrillicVowelsSet.find(str[i]) != cyrillicVowelsSet.end())
                if (cVowelCount == 2)
                {
                    wordsWithMoreThan2CrillicVowels.push_back(str);
                    break;
                }
                else
                    cVowelCount++;
        }
        if (getchar() == '\n')
            break;
    }
    for (auto el : wordsWithMoreThan2CrillicVowels)
        std::cout << el << " ";
    return 0;
}
