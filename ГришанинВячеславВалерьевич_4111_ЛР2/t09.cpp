// Одномерные массивы
// Вводится длина одномерного массива (вектора) и значения его элементов.
// 9.	Составить и вывести на экран массив номеров элементов исходного вектора, встречающихся один раз (уникальных элементов).

// Из примеров прикрепленных к работе(https://study.rea.ru/pluginfile.php/70978/mod_forum/post/147634/Массив_Задача%201.docx),
// следует что в задании под "массивом" подразумевается не только статический массив и динамический массив, но и stl вектор.
// В тексте задания не сказано какие значения вводятся. Будем считать, что имелись в виду целые числа в диапазоне [INT_MIN; INT_MAX]

#include <iostream>
#include <vector>
int main()
{
  int* arr;
  unsigned size;
  std::vector<unsigned> uvIndexVec;
  std::cin >> size;
  arr = new int[size];
  for(unsigned i = 0; i < size; i++)
    std::cin >> arr[i];
  for(unsigned i = 0; i < size; i++)
  {
    for(unsigned j = 0; j < size; j++)
     if(arr[i] == arr[j] and j != i)
      goto CONTINUE_OUTER_FOR;
    uvIndexVec.push_back(i);
    std::cout << uvIndexVec.back() << " ";
    CONTINUE_OUTER_FOR:;
  }
  return 0;
}
