// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 10. Составить и вывести на экран два массива: массив повторяющихся элементов исходного массива и массив их частот.

// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX]
#include <iostream>
#include <vector>
void bubbleSortArr(int* arr, unsigned size)
{
  int temp;
  for(unsigned i = 0; i < size-1; i++)
    for (unsigned j = 0; j < size - i - 1; j++)
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
}
int main()
{
  int* arr;
  unsigned size;
  std::vector<int* > nonuvsVec;
  std::vector<int> nonuvsFVec;
  std::cin >> size;
  arr = new int[size];
  for(unsigned i = 0; i < size; i++)
    std::cin >> arr[i];
  bubbleSortArr(arr, size);
  for(unsigned i = 0, freq = 0; i < size; i++)
  {
    if(i == size - 1)
    {
      if(arr[i] == *nonuvsVec.back())
      {
        nonuvsVec.push_back(arr+i);
        freq++;
        nonuvsFVec.push_back(freq);
      }
    }
    else if(arr[i] == arr[i+1])
    {
      nonuvsVec.push_back(arr+i);
      freq++;
    }
    else
    {
      if(nonuvsVec.size() != 0 and arr[i] == *nonuvsVec.back())
      {
        nonuvsVec.push_back(arr+i);
        freq++;
        nonuvsFVec.push_back(freq);
      }
      freq = 0;
    }
  }
  std::cout << "non unique values of array: ";
  //for(auto el : nonuvsVec)
  for(int i = 0; i < nonuvsVec.size(); i++)
    std::cout << *nonuvsVec[i] << " ";
  std::cout << "\ntheir respective frequency: ";
  //for(auto el : nonuvsFVec)
  for(int i = 0; i < nonuvsFVec.size(); i++)
    std::cout << nonuvsFVec[i] << " ";
  return 0;
}
