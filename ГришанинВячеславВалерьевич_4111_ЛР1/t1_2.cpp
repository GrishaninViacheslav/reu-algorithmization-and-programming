// Задание для решения задач с числами
// Ввести три числа
// 2.	Вывести числа в убывающей последовательности.
#include <iostream>
int main()
{
  int a, b, c, temp;
  std::cin >> a >> b >> c;
  if (b > c)
  {
    temp = b;
    b = c;
    c = temp;
  }
  if (b < a)
  {
    temp = b;
    b = a;
    a = temp;
  }
  if (b > c)
  {
    temp = b;
    b = c;
    c = temp;
  }
  std::cout << c << " " << b << " " << a;
  return 0;
}
