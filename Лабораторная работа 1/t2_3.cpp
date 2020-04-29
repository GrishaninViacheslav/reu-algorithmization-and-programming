// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 3.	Нахожденcия произведения последовательности чисел.
#include <iostream>
int main()
{
  int currNum, product = 1;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;
    product *= currNum;
  }
  std::cout << product;
  return 0;
}
