// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 7.	Подсчета количества положительных, отрицательных и нулевых чисел.
#include <iostream>
int main()
{
  int currNum;
  unsigned posCount = 0, negCount = 0, zeroCount = 0;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;
    if(currNum > 0)
      posCount++;
    else if(currNum < 0)
      negCount++;
    else
      zeroCount++;
  }
  std::cout << "pos count: " << posCount
            << ";\nneg count: " << negCount
            << ";\nzero count: " << zeroCount << ";\n";
  return 0;
}
