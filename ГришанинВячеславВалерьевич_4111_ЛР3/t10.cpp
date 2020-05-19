// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 10. Удалить строки матрицы, где все элементы простые числа.

// В тексте задания нет уточнения, что значит "удалить строку массива",
// предположим, что под этим имеется в виду освобождение блока памяти в
// котором хранятся значения строки и обнуление указателя на эту строку.
// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.

#include <iostream>
#include <cmath>
int minDivisor(int n, int iter = 2);
int main()
{
    unsigned rowCount, columnCount;
    int** matrix;
    std::cin >> rowCount >> columnCount;
    matrix = new int* [rowCount];
    for (unsigned i = 0; i < rowCount; i++)
    {
        matrix[i] = new int[columnCount];
        for (unsigned j = 0; j < columnCount; j++)
            std::cin >> matrix[i][j];
    }
    for (unsigned i = 0; i < rowCount; i++)
    {
        bool isRowPrime = true;
        for (unsigned j = 0; j < columnCount; j++)
            if (isRowPrime && minDivisor(matrix[i][j]) != matrix[i][j])
                isRowPrime = false;
        if (isRowPrime)
        {
            for (unsigned k = i; k < rowCount - 1; k++)
                for (unsigned j = 0; j < columnCount; j++)
                    matrix[k][j] = matrix[k + 1][j];
            delete[] matrix[rowCount - 1];
            matrix[rowCount - 1] = NULL;
            --rowCount;
            --i;
        }
    }
    for (unsigned i = 0; i < rowCount; i++)
    {
        for (unsigned j = 0; j < columnCount; j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
    return 0;
}
int minDivisor(int n, int iter)
{
    return (iter <= sqrt(n)) ? ((n % iter) ? minDivisor(n, iter + 1) : iter) : n;
}
