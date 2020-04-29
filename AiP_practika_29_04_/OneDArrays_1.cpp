// Задания на практическое занятие:
// Массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 10. Создать новый массив из четных чисел этой последовательности.
// Вывести новый массив на экран или, если таких чисел нет, то вывести соответствующее сообщение.
#include <iostream>
int main()
{
  unsigned lenght, evenNumsArrLenght = 0;
  std::cin >> lenght;
  int* arr = new int [lenght];
  for(unsigned i = 0; i < lenght; i++)
  {
    std::cin >> arr[i];
    if(arr[i]%2 == 0)
      evenNumsArrLenght++;
  }
  int* evenNumsArr = new int [evenNumsArrLenght];
  for(unsigned i = 0, t = 0; i < lenght; i++)
    if(arr[i]%2 == 0)
    {
      evenNumsArr[t] = arr[i];
      t++;
    }

  {
    int temp;
    for (unsigned i = 0; i < evenNumsArrLenght - 1; i++)
        for (unsigned j = 0; j < evenNumsArrLenght - i - 1; j++)
            if (evenNumsArr[j] > evenNumsArr[j + 1])
            {
                temp = evenNumsArr[j];
                evenNumsArr[j] = evenNumsArr[j + 1];
                evenNumsArr[j + 1] = temp;
            }
  }

  std::cout << ((evenNumsArrLenght > 0)?"evens: ":"NO EVENS");
  for(unsigned i = 0; i < evenNumsArrLenght; i++)
  {
    while(i != 0 and evenNumsArr[i] == evenNumsArr[i-1])
    {
      for(unsigned j = i; j < evenNumsArrLenght-1; j++)
        evenNumsArr[j] = evenNumsArr[j+1];
      delete (evenNumsArr+evenNumsArrLenght-1);
      evenNumsArrLenght--;
    }
    std::cout << evenNumsArr[i] << " ";
  }

  delete [] arr; //??? откуда берется размер массива?
  delete [] evenNumsArr; //??? откуда берется размер массива?
  return 0;
}
