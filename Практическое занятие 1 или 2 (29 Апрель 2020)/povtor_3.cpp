// Задания на практическое занятие:
// Повтор
// 3. Ввести целое положительное число. Найти сумму цифр введенного числа.
#include <iostream>
int main()
{
  unsigned num, dSum = 0;
  std::cin >> num;
  for(unsigned currNum = num, currDigit = unsigned(currNum)%10; currNum > 0; currNum /= 10, currDigit = unsigned(currNum)%10)
    dSum+=currDigit;
  std::cout << dSum;
  return 0;
}
