// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 8. Составить и вывести на экран массив из различных (по значению) элементов исходного массива.

// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX]

#include <iostream>
#include <vector>
#define ITO(b) for(unsigned i = 0; i < b; i++)
int main()
{
	int* arr;
	unsigned size;
	std::vector<int*> uVec;
	std::cin >> size;
	arr = new int[size];
	ITO(size)
	{
		std::cin >> arr[i];
		uVec.push_back(arr + i);
	}
	{
		int* temp;
		ITO(size - 1)
			for (unsigned j = 0; j < size - i - 1; j++)
				if (*uVec[j] > * uVec[j + 1])
				{
					temp = uVec[j];
					uVec[j] = uVec[j + 1];
					uVec[j + 1] = temp;
				}
	}
	ITO(uVec.size())
	{
		while (i != 0 and i < uVec.size() and *uVec[i] == *uVec[i - 1])
		{
			for (unsigned j = i; j < uVec.size() - 1; j++)
				uVec[j] = uVec[j + 1];
			uVec.pop_back();
		}
	}
	for (auto el : uVec)
		std::cout << *el << " ";
	return 0;
}
