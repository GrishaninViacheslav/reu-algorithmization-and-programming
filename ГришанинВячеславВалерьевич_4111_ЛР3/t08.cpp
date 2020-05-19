// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 8. Составить вектор из номеров строк, где содержатся только трехзначные числа.

// В тексте нет информации о том в какой системе счсиления представляются числа,
// предположим, что все числа в матрице представленны в десятичной системе счисления.
// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.

#include <iostream>
#include <vector>
unsigned digitCountInDec(int);
int main()
{
    unsigned rowCount, columnCount;
    int** matrix;
    std::vector<unsigned> columnsEveryNumThreeDigit_indexes;
    std::cin >> rowCount >> columnCount;
    matrix = new int* [rowCount];
    for (unsigned i = 0; i < rowCount; i++)
    {
        matrix[i] = new int[columnCount];
        bool isEveryNumIsThreeDigit = true;
        for (unsigned j = 0; j < columnCount; j++)
        {
            std::cin >> matrix[i][j];
            if (isEveryNumIsThreeDigit and digitCountInDec(matrix[i][j]) != 3)
                isEveryNumIsThreeDigit = false;
        }
        if (isEveryNumIsThreeDigit)
            columnsEveryNumThreeDigit_indexes.push_back(i + 1);
    }
    for (auto el : columnsEveryNumThreeDigit_indexes)
        std::cout << el << " ";
    return 0;
}
unsigned digitCountInDec(int decNum)
{
    unsigned digitsCount = 1;
    while (decNum /= 10) digitsCount++;
    return digitsCount;
}
