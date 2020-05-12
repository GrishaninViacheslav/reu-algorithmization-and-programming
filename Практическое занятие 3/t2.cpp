// 2. Ввести массив обычным образом,
//    определить два указателя вида int *X
//    используя первый указатель вывести элементы с четными номерами
//    используя второй указатель вывести элементы с нечетными номерами

// Если я правильно понял номер == порядковый номер. Порядковые номера - натуральные числа.
// В тексте задания нет информации о том как вычисляется размер массива.
// Будем считать, что размер массива вводится и полученное значение передается в эти функции.
// После этого вводятся значения элементов массива.

#include <iostream>
void coutArr(int*, unsigned);
int main()
{
	int* arr, * evenIndexArr, * oddIndexArr;
	unsigned arrSize, eiArrSize, oiArrSize;
	std::cin >> arrSize;
	eiArrSize = arrSize / 2;
  oiArrSize = arrSize - eiArrSize;
	arr = new int[arrSize];
	evenIndexArr = new int[eiArrSize];
	oddIndexArr = new int[oiArrSize];
	for (unsigned i = 0, ei = 0, oi = 0; i < arrSize; i++)
	{
		std::cin >> arr[i];
		if ((i+1) % 2)
			oddIndexArr[oi++] = arr[i];
		else
			evenIndexArr[ei++] = arr[i];
	}
	std::cout << "even index elements: ";
	coutArr(evenIndexArr, eiArrSize);
	std::cout << "\nodd index elements: ";
	coutArr(oddIndexArr, oiArrSize);
	return 0;
}
void coutArr(int* a, unsigned s)
{
	for (unsigned i = 0; i < s; i++)
		std::cout << a[i] << " ";
}
