// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 14. Если  все элементы этого массива упорядочены по неубыванию или по невозрастанию,
// то найти элемент, сумма цифр которого максимальна
/*
    Re: Лабораторное занятие 2. Подгруппа 1
    от Нина Викторовна Комлева - Вторник, 12 Май 2020, 21:18
    3, 5, 78, 99 упорядочен по неубыванию
    65, 43, 43, 5 упорядочен по невозрастанию
    25, 17, 88, 14 не подходит под это условие
*/

// Не уверен, но вроде сумму цифр можно найти только для положительных чисел.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду натуральные числа в диапазоне [0; INT_MIN+INT_MAX]
// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.

#include <iostream>
unsigned digitsSum(unsigned);
int main()
{
  unsigned* arr, *elPtr;
  unsigned size, maxDigitSum = 0;
  bool defineEl = false;
  char riseDir = 's'; // s - streight, arr[i] == arr[i-1]; u - upp, arr[i] > arr[i-1]; d - down, arr[i] < arr[i-1];
  std::cin >> size;   // x - неубывает или невозрастает, наверное
  arr = new unsigned[size];
  for(unsigned i = 0; i < size; i++)
  {
    std::cin >> arr[i];
    if(digitsSum(arr[i]) > maxDigitSum)
    {
      maxDigitSum = digitsSum(arr[i]);
      elPtr = (arr + i);
    }
    if(i == 0)
      continue;
    if(riseDir == 's')
    {
      if(arr[i] < arr[i-1])
      {
        riseDir = 'd';
        defineEl = true;
      }
      else if(arr[i] > arr[i-1])
      {
        riseDir = 'u';
        defineEl = true;
      }
    }
    else if(arr[i] < arr[i-1] and (riseDir == 'u' or riseDir == 's') || arr[i] > arr[i-1] and (riseDir == 'd' or riseDir == 's'))
      riseDir = 'x';
  }
  if(riseDir != 'x')
    std::cout << *elPtr;
  return 0;
}
unsigned digitsSum(unsigned num)
{
  unsigned sum = 0;
  for(; num > 0; num/=10)
    sum += num%10;
  return sum;
}
