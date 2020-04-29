// Задания на практическое занятие:
// Повтор
// 1. Ввести три числа, определяющие размер отрезков, определить,
// можно ли из данных отрезков составить треугольник, если да,
// то проверить будет ли треугольник равнобедренным или прямоугольным.
#include <iostream>
int main()
{
  float a, b, c;
  std::cin >> a >> b >> c;
  if(b+c > a && a+c > b && a+b > c)
    std::cout << "segments FORM a triangle\n"
                 "triangle\n  is" << ((a == b || a == c || b == c)?" ":" NOT ") << "isosceles\n"
                           "  and" << ((a*a+b*b==c*c || a*a+c*c==b*b || b*b+c*c==a*a)?" ":" DO NOT ") << "have a right angle";
  else
    std::cout << "segments do NOT form a triangle\n";
  return 0;
}
