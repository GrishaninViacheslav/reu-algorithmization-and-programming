// Задание для решения задач с числами
// Ввести три числа
// 3.	Вывести максимальное значение.
#include <iostream>
int main()
{
  int a, b, c, max = INT_MIN;
  #define updateMax(num) if(num > max) max = num
  std::cin >> a >> b >> c;
  updateMax(a);
  updateMax(b);
  updateMax(c);
  std::cout << max;
  return 0;
}
