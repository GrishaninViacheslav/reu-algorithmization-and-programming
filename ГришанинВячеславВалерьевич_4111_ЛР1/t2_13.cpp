// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 13. Определения порядкового номера максимального числа.
#include <iostream>
int main()
{
  int currNum, max = -INT_MAX;
  unsigned numCount = 0, maxNumIndex = 1;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;

    numCount++;
    if(currNum > max)
    {
      max = currNum;
      maxNumIndex = numCount;
    }
  }
  std::cout << maxNumIndex;
  return 0;
}
