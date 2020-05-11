// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 13.	Если среди элементов массива есть хотя бы одно число Фибоначчи, то вектор инвертировать.

// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX]

#include <iostream>
bool isFibonachi(int);
void reverseArr(int*, unsigned);
int main()
{
  int* arr;
  unsigned size;
  bool toReverse = false;
  std::cin >> size;
  arr = new int[size];
  for(unsigned i = 0; i < size; i++)
  {
    std::cin >> arr[i];
    if(!toReverse && isFibonachi(arr[i]))
      toReverse = true;
  }
  if(toReverse)
    reverseArr(arr, size);
  for(unsigned i = 0; i < size; i++)
    std::cout << arr[i] << " ";
  return 0;
}
bool isFibonachi(int num)
{
  int bBFNum = 1, bFNum = 1, fibNum = 1;
  bool isFib = false;
  for (int i = 1; i < num; i++)
  {
    bFNum = bBFNum;
    bBFNum = fibNum;
    fibNum = bFNum + bBFNum;
    if(num == fibNum)
      isFib = true;
  }
  return isFib or num == 1;
}
void reverseArr(int* arr, unsigned size)
{
  int temp;
  for(unsigned i = 0; i < size/2; i++)
  {
    temp = arr[i];
    arr[i] = arr[size-1-i];
    arr[size-1-i] = temp;
  }
}
