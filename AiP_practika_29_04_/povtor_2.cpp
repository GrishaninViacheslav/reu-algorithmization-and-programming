// Задания на практическое занятие:
// Повтор
// 2. Ввести число. Выдать цифры, входящие в число, на экран, начиная с последней цифры.
// В тексте задания не уточнено о каких именно числах идет речь.
// Если я правильно понял задание, то имеются в виду натуральные цисла.
#include <iostream>
int main()
{
  unsigned num;
  std::cin >> num;
  for(unsigned currNum = num, currDigit = unsigned(currNum)%10; currNum > 0; currNum /= 10, currDigit = unsigned(currNum)%10)
    std::cout << currDigit << " ";
  return 0;
}
