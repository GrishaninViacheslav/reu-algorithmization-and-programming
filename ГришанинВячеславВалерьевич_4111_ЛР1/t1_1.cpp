// Задание для решения задач с числами
// Ввести три числа
// 1.	Вывести числа в возрастающей последовательности.
#include <iostream>
int main()
{
  int a, b, c, temp;
  cin >> a >> b >> c;
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
  std::cout << a << " " << b << " " << c;
  return 0;
}
