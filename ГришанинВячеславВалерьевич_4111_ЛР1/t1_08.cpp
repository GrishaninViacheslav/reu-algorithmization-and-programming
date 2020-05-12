// Задание для решения задач с числами
// Ввести три числа
// 8.	Вывести номер числа, имеющего среднее по величине значение.
// В задания не уточнено что делать, если такого числа нет,
#include <iostream>
int main()
{
  int a, b, c;
  #define avg (a+b+c)/3.f
  std::cin >> a >> b >> c;
  if(a == avg)
    std::cout << 1;
  else if(b == avg)
    std::cout << 2;
  else if(c == avg)
    std::cout << 3;
  return 0;
}
