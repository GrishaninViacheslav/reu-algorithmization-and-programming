// Лабораторная работа № 4
// Тема: « Обработка символьной информации и строк»
// Задание: Ввести строку символов ( предусмотреть ввод пустой строки или строки из одних пробелов).
// Разделителями слов в строке являются пробелы (один или несколько).
// 9. Определить номера слов, в которых содержится больше одного цифрового символа.

#include <iostream>
#include <vector>
#include <cstdio>
int main()
{
	std::string str;
	std::vector<int> wordsWithMoreThan1Digit;
	{
		bool hasDigit = false;
		for (unsigned currWordIndex = 1; (std::cin >> str); currWordIndex++, hasDigit = false)
		{
			for (unsigned i = 0; i < str.size(); i++)
				if (str[i] >= 48 and str[i] <= 57)
					if (hasDigit)
					{
						wordsWithMoreThan1Digit.push_back(currWordIndex);
						break;
					}
					else
						hasDigit = true;
			if (getchar() == '\n')
				break;
		}
	}
	for (auto el : wordsWithMoreThan1Digit)
		std::cout << el << " ";
	return 0;
}
