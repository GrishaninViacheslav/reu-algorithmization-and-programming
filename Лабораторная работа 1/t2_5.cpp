// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 5.	Нахождения минимального числа последовательности чисел.
#include <iostream>
#include <float.h>
int main()
{
  float currNum, min = INT_MAX;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;
    if(currNum < min)
      min = currNum;
  }
  std::cout << min;
  return 0;
}
