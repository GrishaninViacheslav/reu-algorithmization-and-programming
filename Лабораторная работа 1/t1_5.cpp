// Задание для решения задач с числами
// Ввести три числа
// 5.	Вывести номер максимального числа.
#include <iostream>
int main()
{
  int a, b, c, max = INT_MIN, index;
  std::cin >> a >> b >> c;
  if(a > max)
  {
    max = a;
    index = 1;
  }
  if(b > max)
  {
    max = b;
    index = 2;
  }
  if(c > max)
  {
    max = c;
    index = 3;
  }
  std::cout << index;
  return 0;
}
