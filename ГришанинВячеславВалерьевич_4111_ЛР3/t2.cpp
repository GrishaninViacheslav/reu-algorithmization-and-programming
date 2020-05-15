// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 2. Составить вектор из номеров строк, где все элементы простые числа.

// В тексте задания нет информации о том какие значения вводятся. Будем считать, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// будем считать что ввод происходит последовательно по строкам.

#include <iostream>
int MinDivisor(int n);
int main()
{
    struct
    {
        bool isInitialized;
        unsigned rowCount, columnCount;
        int** matrix;
        void get()
        {
            if (isInitialized)
            {
                for (int i = 0; i < rowCount; i++)
                    delete[] matrix[i];
                delete[] matrix;
            }
            std::cin >> rowCount >> columnCount;
            matrix = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                matrix[i] = new int[columnCount];
            for (unsigned i = 0; i < rowCount; i++)
                for (unsigned j = 0; j < columnCount; j++)
                    std::cin >> matrix[i][j];
        }
    } matrix {false};
    std::cout << matrix.isInitialized << std::endl;
    matrix.get();

    return 0;
}
int MinDivisor(int n)
{
    static int d = 1;
    return (d <= sqrt(n)) ? ((n % ++d) ? MinDivisor(n) : d) : n;
}
