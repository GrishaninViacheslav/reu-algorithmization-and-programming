// Задание для решения задач с числами
// Ввести три числа
// 4.	Вывести минимальное значение.
#include <iostream>
int main()
{
  int a, b, c, min = INT_MAX;
  #define updateMin(num) if(num < min) min = num
  std::cin >> a >> b >> c;
  updateMin(a);
  updateMin(b);
  updateMin(c);
  std::cout << min;
  return 0;
}
