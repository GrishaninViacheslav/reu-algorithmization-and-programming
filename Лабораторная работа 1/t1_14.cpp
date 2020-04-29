// Задание для решения задач с числами
// Ввести три числа
// 14.	Вывести сообщение является ли сумма чисел кратной 3 или нет.
#include <iostream>
int main()
{
  int a, b, c;
  std::cin >> a >> b >> c;
  std::cout << "the sum is" << ( ((a+b+c)%3)?" NOT ":" " ) << "a multiple of 3";
  return 0;
}
