// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 2. Составить вектор из номеров строк, где все элементы простые числа..

// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.
#include <iostream>
#include <cmath>
#include <vector>
int MinDivisor(int n, int iter = 2);
int main()
{
    unsigned rowCount, columnCount;
    int** matrix;
    std::vector<unsigned> primeRawsIndexes;
    std::cin >> rowCount >> columnCount;
    matrix = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        matrix[i] = new int[columnCount];
    {
        bool isRowPrime;
        for (unsigned i = 0; i < rowCount; i++)
        {
            isRowPrime = true;
            for (unsigned j = 0; j < columnCount; j++)
            {
                std::cin >> matrix[i][j];
                if (MinDivisor(matrix[i][j]) != matrix[i][j])
                    isRowPrime = false;
            }
            if (isRowPrime)
                primeRawsIndexes.push_back(i + 1);
        }
    }
    for (auto el : primeRawsIndexes)
        std::cout << el << " ";
    return 0;
}
int MinDivisor(int n, int iter)
{
    return (iter <= sqrt(n)) ? ((n % iter) ? MinDivisor(n, iter + 1) : iter) : n;
}
