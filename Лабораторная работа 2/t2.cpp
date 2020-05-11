// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 2.	Поменять местами максимальный и минимальный элементы массива. Вывести измененный массив на экран.

// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX].
// В тексте задания не определено поведение программы: какие переменные нужно менять местами, если в массиве несколько равных
// наименьшийх значений или несколько равных наибольших значений. Будем считать, что под минимальным и максимальным элементом массива
// подразумевались первый(с наименьшим индеком) элемент c соответственно наименьшим и наибольшим значением.
#include <iostream>
void swapInts(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
int main()
{
  int** intPtrArr;
  unsigned size;
  int maxValPtr = 0, minValPtr = 0;
  std::cin >> size;
  intPtrArr = new int* [size];
  for(int i = 0, currVal; i < size; i++)
  {
    std::cin >> currVal;
    intPtrArr[i] = new int(currVal);
    if(*intPtrArr[i] > *intPtrArr[maxValPtr])
      maxValPtr = i;
    else if(*intPtrArr[i] < *intPtrArr[minValPtr])
      minValPtr = i;
  }
  swapInts(intPtrArr[maxValPtr], intPtrArr[minValPtr]);
  std::cout << "result arr: ";
  for(int i = 0, currVal; i < size; i++)
    std::cout << *intPtrArr[i] << " ";
  return 0;
}
