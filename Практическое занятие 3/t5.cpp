// 5. Дано натуральное число n > 1. Выведите его наименьший делитель, отличный от 1.
// Решение оформите в виде функции MinDivisor(n). Количество операций в программе должно быть пропорционально корню из n.
// Указание. Если у числа n нет делителя, меньшего n , то число n — простое и ответом будет само число n.

#include <iostream>
#include <cmath>
int MinDivisor(int n, int iter = 2);
int main()
{
  int num;
  std::cin >> num;
  std::cout << MinDivisor(num);
  return 0;
}
int MinDivisor(int n, int iter) // Я не умею вычислять сложность функции. Не уверен, что кооличество операций пропорционально корню из n
{
  return (iter <= sqrt(n))?((n % iter)?MinDivisor(n, iter+1):iter):n;
}
