// Задание для решения задач с числами
// Ввести три числа
// 9.	Третье число определяет код операции, который нужно выполнить с первыми двумя числами, следующим образом:
// 1 - ‘+’,   2 - ‘-’,   3 -‘*’. Вывести результат операции.
#include <iostream>
int main()
{
  int a, b, c;
  #define avg (a+b+c)/3.f
  std::cin >> a >> b >> c;
  switch(c)
  {
    case 1:
      std::cout << a + b;
      break;
    case 2:
      std::cout << a - b;
      break;
    case 3:
      std::cout << a * b;
      break;
  }
  return 0;
}
