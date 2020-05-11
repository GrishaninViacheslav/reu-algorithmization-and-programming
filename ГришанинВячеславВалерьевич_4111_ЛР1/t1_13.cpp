// Задание для решения задач с числами
// Ввести три числа
// 13. Вывести сообщение является ли произведение чисел четным числом или нет.
#include <iostream>
int main()
{
  int a, b, c;
  std::cin >> a >> b >> c;
  std::cout << "nums product is " << ((a*b*c%2)?"odd":"even");
  return 0;
}
