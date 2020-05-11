// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 11.	Найти сумму наибольшей по длине возрастающей последовательности подряд идущих элементов массива.
// Если таких последовательностей несколько, вывести сумму элементов первой такой последовательности.

// В тексте задания не определенно поведение программы в том случае если в массиве нет возрастающей последовательности.
// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX]

#include <iostream>

int main()
{
  int* arr;
  unsigned size;
  int sum = 0;
  bool isSumDefined = false;
  unsigned length = 0;
  std::cin >> size;
  arr = new int[size];
  {
    int currSum = 0;
    unsigned currLenght = 1;
    for(unsigned i = 0; i < size; i++)
    {
      std::cin >> arr[i];
      if(i == 0)
        continue;
      if(arr[i] > arr[i-1])
      {
        currLenght++;
        currSum += arr[i-1];
        if(!isSumDefined)
          isSumDefined = true;
        if(i == size - 1)
        {
          currSum += arr[i];
          if(currLenght > length)
          {
            length = currLenght;
            sum = currSum;
          }
        }
      }
      else if(i != 1)
      {
        if(arr[i-1] > arr[i-2])
          currSum += arr[i-1];
        if(currLenght > length)
        {
          length = currLenght;
          sum = currSum;
        }
        currSum = 0;
        currLenght = 1;
      }
    }
  }
  if(isSumDefined)
    std::cout << sum;
  return 0;
}
