// 3. Напишите функцию min(a, b), вычисляющую минимум двух чисел.
// Затем напишите функцию min4(a, b, c, d), вычисляющую минимум 4 чисел
// с помощью функции min. Считайте четыре целых числа и выведите их минимум.

#include <iostream>
int min(int, int);
int min4(int, int, int, int);
int main()
{
  int a, b, c, d;
  std::cin >> a >> b >> c >> d;
  std::cout << min4(a, b, c, d);
  return 0;
}
int min(int a, int b)
{
    return (a < b)?a:b;
}
int min4(int a, int b, int c, int d)
{
    return min( min(a, b), min(c, d) );
}
