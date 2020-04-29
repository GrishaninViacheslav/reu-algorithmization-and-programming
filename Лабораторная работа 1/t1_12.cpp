// Задание для решения задач с числами
// Ввести три числа
// 12. Первые два числа - интервал. Вывести сообщение,
// меньше ли третье число нижней границы интервала.
#include <iostream>
int main()
{
  int a, b, c;
  std::cin >> a >> b >> c;
  if(a > b)
  {
    int temp = a;
    a = b;
    b = temp;
  }
  std::cout << "third num(" << c << ") " << ((c < a)?"<":">=") << " interval lower limit(" << a << ")\n";
  return 0;
}
