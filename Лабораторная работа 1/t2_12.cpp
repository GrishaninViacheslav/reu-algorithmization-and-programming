// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 12. Определения порядкового номера минимального числа.
#include <iostream>
int main()
{
  int currNum, min = INT_MAX;
  unsigned numCount = 0, minNumIndex = 1;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;

    numCount++;
    if(currNum < min)
    {
      min = currNum;
      minNumIndex = numCount;
    }
  }
  std::cout << minNumIndex;
  return 0;
}
