// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 2.	Нахождения суммы последовательности чисел.
#include <iostream>
int main()
{
  int currNum, sum = 0;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;
    sum += currNum;
  }
  std::cout << sum;
  return 0;
}
