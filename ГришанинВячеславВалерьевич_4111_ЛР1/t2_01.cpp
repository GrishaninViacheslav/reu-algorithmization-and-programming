// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 1.	Нахождения количества чисел в последовательности.
#include <iostream>
int main()
{
  int currNum;
  unsigned numCount = 0;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;
    numCount++;
  }
  std::cout << numCount;
  return 0;
}
