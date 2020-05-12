// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 12.	Определить сумму тех элементов этого массива, которые содержат только нечетные цифры.

// В тексте задания не определенно поведение программы в том случае если у всех элементов все цифры четные.
// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX]

#include <iostream>
bool isNumsDigitsOdd(int);
int main()
{
  int* arr;
  unsigned size;
  int sum = 0;
  bool isSumDefined = false;
  std::cin >> size;
  arr = new int[size];
  for(unsigned i = 0; i < size; i++)
  {
    std::cin >> arr[i];
    if(isNumsDigitsOdd(arr[i]))
    {
      sum += arr[i];
      if(!isSumDefined)
        isSumDefined = true;
    }
  }
  if(isSumDefined)
    std::cout << sum;
  return 0;
}
bool isNumsDigitsOdd(int num)
{
  bool isdOdd = true;
  for(; num > 0; num /= 10)
    if(num%10%2 == 0)
    {
      isdOdd = false;
      break;
    }
  return isdOdd;
}
