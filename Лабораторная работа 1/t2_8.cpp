// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 8.	Подсчета количества пар чисел, у которых первое число равно второму.  Длина последовательности кратна 2.
/*
      количество пар чисел которые идут подряд и равны
      для последовательности 3, 5, 5, 5, 7, 6, 6, 2, 777
      ответ 3

      количество пар чисел которые идут подряд и равны;
      Например если:
      число 1) 3.4
      число 2) 3.4
      число 3) 3.4
      число 4) -12
      число 5) 3.4
      то пары: (1 и 2), (2 и 3)
*/
// Задание для решения задач с последовательностями чисел.
// Вводится последовательность чисел. Признак конца ввода - число 777.
// Составить программы для:
// 1.	Нахождения количества чисел в последовательности.
#include <iostream>
int main()
{
  int currNum, lastNum;
  unsigned pairCount = 0;
  std::cin >> lastNum;
  //while (lastNum != 777)
  while (true)
  {
    std::cin >> currNum;
    if (currNum == 777)
      break;
    if(currNum == lastNum)
      pairCount++;
    lastNum = currNum;
  }
  std::cout << pairCount;
  return 0;
}
