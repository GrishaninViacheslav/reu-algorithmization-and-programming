// Задание для решения задач с числами
// Ввести три числа
// 11. Первые два числа - интервал. Вывести сообщение,
// больше ли третье число верхней границы интервала.
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
  std::cout << "third num(" << c << ") " << ((c > b)?">":"<=") << " interval upper limit(" << b << ")\n";
  return 0;
}
