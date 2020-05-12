// 4. Даны четыре действительных числа: x1, y1, x2, y2.
// Напишите функцию distance(x1, y1, x2, y2), вычисляющую расстояние между точкой (x1. y1) и (x2, y2).
// Считайте четыре действительных числа и выведите результат работы этой функции.

#include <iostream>
#include <cmath>
float distance(float, float, float, float);
int main()
{
  float x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;
  std::cout << distance(x1, y1, x2, y2);
  return 0;
}
float distance(float x1, float y1, float x2, float y2)
{
  return sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}
