// 6. Напишите функцию fib(n), которая по данному целому положительному n возвращает n-e число Фибоначчи.
// В этой задаче нельзя использовать циклы - используйте рекурсию.

#include <iostream>
int fibonacci(int);
int main()
{
  int num;
  std::cin >> num;
  std::cout << fibonacci(num);
  return 0;
}
int fibonacci(int n)
{
  return (n == 1 || n == 2)?1:(fibonacci(n - 1) + fibonacci(n - 2));
}
