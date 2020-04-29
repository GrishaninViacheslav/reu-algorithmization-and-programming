// Задания на практическое занятие:
// Массивы
// 11. Создать новый массив из чисел находящихся в диапазоне [b1, b2],
// значение границ диапазона вводится с клавиатуры.
// Вывести новый массив на экран или, если таких чисел нет,
// то вывести соответствующее сообщение.
#include <iostream>
#include <vector>
int main()
{
	std::vector<int> b1b2Numsvec;
	float b1, b2;
	std::cin >> b1 >> b2;
	if (b1 > b2)
	{
		float temp = b1;
		b1 = b2;
		b2 = temp;
	}
	#define largerRound(num) ((num - (float)int(num)) ? int(num) + 1 : num)
	for (int i = largerRound(b1); i <= int(b2); i++)
		b1b2Numsvec.push_back(i);

	if (b1b2Numsvec.size() > 0)
		for (auto el : b1b2Numsvec)
			std::cout << el << " ";
	else
		std::cout << "no integers in range [" << b1 << "; " << b2 << "]";
	return 0;
}
