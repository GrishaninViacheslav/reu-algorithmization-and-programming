// Задание для решения задач с числами
// Ввести три числа
// 7.	Вывести число, имеющее среднее по величине значение.
// В задании не уточненно что делать, если такого числа нет.
#include <iostream>
int main()
{
  int a, b, c;
  #define avg (a+b+c)/3.f
  std::cin >> a >> b >> c;
  if(a == avg)
    std::cout << a;
  else if(b == avg)
    std::cout << b;
  else if(c == avg)
    std::cout << c;
  return 0;
}
