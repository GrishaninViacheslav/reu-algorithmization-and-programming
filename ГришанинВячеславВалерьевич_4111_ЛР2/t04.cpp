// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 4.	Вводится дополнительный массив разрешенных значений.
// Определить и вывести на экран, сколько элементов исходного массива имеют разрешенные значения.

// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX]
// В тексте задания неопределенн формат ввода дополнительного массива разрешенных значений.
// Будем считать что ввод значений дополнительного массива разрешенных значений происходит
// после вывода сообщения "permitted values: ". Значения вводятся через пробел(Space).
// Ввод значений дополнительного массива разрешенных значений заканчивается после получения EOF(Ctrl-Z).

#include <iostream>
#include <limits>
#include <vector>
int main()
{
	unsigned size;
	int* arr;
	std::vector<int> permittedValsVec;
	unsigned permittedValsInArrCounter = 0;
	std::cin >> size;
	arr = new int[size];
	for (int i = 0; i < size; i++)
		std::cin >> arr[i];
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "permitted values: ";
	for (int pv; std::cin >> pv; )
		permittedValsVec.push_back(pv);
	for (int i = 0; i < size; i++)
		for (auto permittedVal : permittedValsVec)
			if (arr[i] == permittedVal)
			{
				permittedValsInArrCounter++;
				break;
			}
	std::cout << "count of permitted values in first array: " << permittedValsInArrCounter;
	return 0;
}
