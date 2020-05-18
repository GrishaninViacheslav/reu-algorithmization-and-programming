// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 6. Составить вектор из номеров столбцов, где все элементы являются числовыми палиндромами.

// В тексте нет информации о том в какой системе счсиления представляются числа,
// предположим, что все числа в матрице представленны в одной из позиционных.
// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.
#include <iostream>
#include <stdlib.h>
#include <vector>
bool isStrPolindrome(std::string);
int main()
{
    int rowCount, columnCount;
    std::string** matrix;
    std::vector<int> columnsWithEveryNumPolindrome_indexes;
    std::cin >> rowCount >> columnCount;
    matrix = new std::string * [rowCount];
    for (int i = 0; i < rowCount; i++)
        matrix[i] = new std::string[columnCount];
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < columnCount; j++)
            std::cin >> matrix[i][j]; // Не понимаю предупреждение MVS: "Reading invalid data from 'matrix[i]':  the readable size is '(unsigned int)*24+4' bytes, but '48' bytes may be read."
    {
        bool isColumnPolindrome;
        for (int j = 0; j < columnCount; j++)
        {
            isColumnPolindrome = true;
            for (int i = 0; i < rowCount; i++)
                if (!isStrPolindrome(matrix[i][j]))
                    isColumnPolindrome = false;
            if (isColumnPolindrome)
                columnsWithEveryNumPolindrome_indexes.push_back(j + 1);
        }
    }
    for (auto el : columnsWithEveryNumPolindrome_indexes)
        std::cout << el << " ";
    return 0;
}
bool isStrPolindrome(std::string str)
{
    for (int i = 0; i < str.size() / 2; i++)
        if (str[i] != str[str.size() - 1 - i])
            return false;
    return true;
}
