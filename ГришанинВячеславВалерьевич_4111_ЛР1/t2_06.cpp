// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 6.	Нахождения среднего арифметического значения последовательности чисел.
#include <iostream>
int main()
{
  int currNum, sum = 0;
  unsigned numCount = 0;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;
    numCount++;
    sum += currNum;
  }
  std::cout << float(sum)/numCount;
  return 0;
}
