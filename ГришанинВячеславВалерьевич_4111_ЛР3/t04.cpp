// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 4. Если среди элементов матрицы есть хотя бы одно простое число, повернуть все ее элементы на 180 градусов против часовой стрелки.

// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.

#include <iostream>
#include <cmath>
int MinDivisor(int n, int iter = 2);
int main()
{
    int rowCount, columnCount;
    int** matrix;
    bool hasPrimeNum = false;
    std::cin >> rowCount >> columnCount;
    matrix = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        matrix[i] = new int[columnCount];
    for (unsigned i = 0; i < rowCount; i++)
        for (unsigned j = 0; j < columnCount; j++)
        {
            std::cin >> matrix[i][j];
            if(!hasPrimeNum and MinDivisor(matrix[i][j]) ==  matrix[i][j])
              hasPrimeNum = true;
        }
    for (unsigned i = 0, iterCount = rowCount*columnCount/2; hasPrimeNum && i < rowCount && iterCount; i++)
        for (unsigned j = 0; j < columnCount and iterCount; j++, iterCount--)
        {
          int temp = matrix[i][j];
          matrix[i][j] = matrix[rowCount-1-i][columnCount-1-j];
          matrix[rowCount-1-i][columnCount-1-j] = temp;
        }
    for (unsigned i = 0; i < rowCount; i++)
    {
      for (unsigned j = 0; j < columnCount; j++)
        std::cout << matrix[i][j] << " ";
      std::cout << std::endl;
    }
    return 0;
}
int MinDivisor(int n, int iter)
{
    return (iter <= sqrt(n)) ? ((n % iter) ? MinDivisor(n, iter + 1) : iter) : n;
}
