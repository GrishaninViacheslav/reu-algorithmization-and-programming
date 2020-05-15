// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 1. Составить массив (вектор) из номеров столбцов матрицы, где есть хотя бы одно число Фибоначчи.

// В тексте задания нет информации о том какие значения вводятся. Будем считать, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// будем считать что ввод происходит последовательно по строкам.
#include <iostream>
#include <set>
bool isFibonacci(int num)
{
    int n1 = 1, n2 = 1;
    while (n2 < num)
    {
        int temp = n2;
        n2 += n1;
        n1 = temp;
    }
    return (n2 == num);
}
int main()
{
    unsigned rowCount, columnCount;
    int** matrix;
    std::set<unsigned> columnsWithFibnumIndexes;
    std::cin >> rowCount >> columnCount;
    matrix = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        matrix[i] = new int[columnCount];
    for (unsigned i = 0; i < rowCount; i++)
        for (unsigned j = 0; j < columnCount; j++)
        {
            std::cin >> matrix[i][j];
            if (isFibonacci(matrix[i][j]) and columnsWithFibnumIndexes.find(j+1) == columnsWithFibnumIndexes.end())
                columnsWithFibnumIndexes.insert(j+1);
        }
    for (auto el : columnsWithFibnumIndexes)
        std::cout << el << " ";
    return 0;
}
