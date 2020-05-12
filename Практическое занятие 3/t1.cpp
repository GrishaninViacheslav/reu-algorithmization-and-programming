// 1.Создать функции
// - ввода целочисленного массива
// - вывода целочисленного массива
// Работа с массивом производится через указатель.
// В функции передается указатель вида int *A

// В тексте задания нет информации о том как вычисляется размер массива.
// Будем считать, что размер массива вводится и полученное значение передается в эти функции.
// После этого вводятся значения элементов массива.

#include <iostream>
void getArr(int*, unsigned);
void coutArr(int*, unsigned);
int main()
{
	int* arr;
	unsigned size;
	std::cin >> size;
	arr = new int [size];
	getArr(arr, size);
	coutArr(arr, size);
	return 0;
}
void getArr(int* a, unsigned s)
{
	//delete [] a;
	//a = new int[s]; //???
	for (int i = 0; i < s; i++)
		std::cin >> a[i];
}
void coutArr(int* a, unsigned s)
{
	for (int i = 0; i < s; i++)
		std::cout << a[i] << " ";
}
