// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 6.	Составить и вывести на экран массив с М максимальными значениями исходного массива. М вводится дополнительно.

// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX]
// В тексте задания не определено однозначно в каком порядке вводятся длина, значения элементов и M.
// Будем считать ввод происходит в следующим порядке:  M, длина, значения элементов;
// Очевидно что по условию M не может быть больше длины исхожного одномернго массива

#include <iostream>
#include <vector>
#include <limits>
#define ITO(b) for(unsigned i = 0; i < b; i++)
int main()
{
	int* arr;
	std::vector<int*> mVec;
	unsigned size, m;
	std::cin >> size;
	arr = new int[size];
	ITO(size)
	{
		std::cin >> arr[i];
		mVec.push_back(arr + i);
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	{
		int* temp;
		ITO(size - 1)
			for (unsigned j = 0; j < size - i - 1; j++)
				if (*mVec[j] < * mVec[j + 1])
				{
					temp = mVec[j];
					mVec[j] = mVec[j + 1];
					mVec[j + 1] = temp;
				}
	}
	std::cout << "M value: ";
	std::cin >> m;
	ITO(size - m)
		mVec.pop_back();
	std::cout << "result: ";
	for(auto mEl : mVec)
		std::cout << *mEl << " ";
	return 0;
}
