// Задание для решения задач с числами
// Ввести три числа
// 6.	Вывести номер минимального числа.
#include <iostream>
int main()
{
  int a, b, c, min = INT_MAX, index;
  std::cin >> a >> b >> c;
  if(a < min)
  {
    min = a;
    index = 1;
  }
  if(b < min)
  {
    min = b;
    index = 2;
  }
  if(c < min)
  {
    min = c;
    index = 3;
  }
  std::cout << index;
  return 0;
}
