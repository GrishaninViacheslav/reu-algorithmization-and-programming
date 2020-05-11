// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 14. Если  все элементы этого массива упорядочены по неубыванию или по невозрастанию,
// то найти элемент, сумма цифр которого максимальна

// Не понимаю смысла условия "все элементы этого массива упорядочены по неубыванию или по невозрастанию", так как
// под это условие подпадает любой массив.
// Не уверен, но вроде сумму цифр можно найти только для положительных чисел.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду натуральные числа в диапазоне [0; INT_MIN+INT_MAX]
// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.

#include <iostream>
unsigned digitsSum(unsigned);
int main()
{
  unsigned* arr, *elPtr;
  unsigned size, maxDigitSum = 0;
  bool defineEl = true;
  std::cin >> size;
  arr = new unsigned[size];
  for(unsigned i = 0; i < size; i++)
  {
    std::cin >> arr[i];
    if(i == 0)
      continue;
    if(!(arr[i] > arr[i-1]) or !(arr[i] < arr[i-1]))
    //if(true)
    {
      if(digitsSum(arr[i]) > maxDigitSum)
      {
        maxDigitSum = digitsSum(arr[i]);
        elPtr = (arr + i);
      }
    }
    else
      defineEl = false;
  }
  if(defineEl)
    std::cout << *elPtr;
  return 0;
}
unsigned digitsSum(unsigned num)
{
  unsigned sum = 0;
  for(; num > 0; num/=10)
    sum += num%10;
  return sum;
}
