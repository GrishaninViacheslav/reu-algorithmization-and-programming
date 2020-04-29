// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 9.	Определения порядковых номеров отрицательных чисел.
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
    if(currNum < 0)
      std::cout << "  neg num index: " << numCount << std::endl;
  }
  return 0;
}
