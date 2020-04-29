// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 14.	Определения порядкового номера последнего нуля.
// В задании не уточнено что делать, если нуля нет в числовой последовательности
#include <iostream>
int main()
{
  int currNum;
  unsigned numCount = 0, lastZeroIndex;
  bool lastZeroIndexDefined = false;
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;

    numCount++;
    if(currNum == 0)
    {
      lastZeroIndex = numCount;
      lastZeroIndexDefined = true;
    }
  }
  if(lastZeroIndexDefined)
    std::cout << lastZeroIndex;
  return 0;
}
