// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 7.	Переписать элементы массива в обратном порядке на том же месте. Вывести измененный массив на экран.

// Еслия я правильно понял задание, то под "на том же месте" подразумевается, что адреса элементов останутся неизменными.
// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX]

#include <iostream>
#define ITO(b) for(unsigned i = 0; i < b; i++)
void coutArrValsNAdd(int* arr, unsigned size)
{
  ITO(size)
    std::cout << arr[i] << "        ";
  std::cout << std::endl;
  ITO(size)
    std::cout << arr+i << " ";
}
int main()
{
  int* arr;
  unsigned size;
  std::cin >> size;
  arr = new int [size];
  ITO(size)
    std::cin >> arr[i];
  std::cout << "INPUT ARR:\n";
  coutArrValsNAdd(arr, size);
  ITO(size/2)
  {
    int temp = arr[i];
    arr[i] = arr[size-1-i];
    arr[size-1-i] = temp;
  }
  std::cout << "\nRESULT:\n";
  coutArrValsNAdd(arr, size);
  return 0;
}
