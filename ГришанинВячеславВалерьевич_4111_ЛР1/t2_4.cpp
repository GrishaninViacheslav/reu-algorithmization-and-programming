// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 4.	Нахождения максимального числа последовательности чисел.
#include <iostream>
#include <float.h>
int main()
{
  float currNum, max = -INT_MAX;
  std::cin >> currNum;
  max = currNum;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;
    if(currNum > max)
      max = currNum;
  }
  std::cout << max;
  return 0;
}
