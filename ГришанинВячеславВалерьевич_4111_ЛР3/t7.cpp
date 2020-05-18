// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 7. Составить вектор из номеров столбцов, где есть хотя бы одно число,
// в котором все цифры одинаковые ( элементы матрицы > 10).

// В тексте нет информации о том в какой системе счсиления представляются числа,
// предположим, что все числа в матрице представленны в одной из позиционных.
// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.

#include <iostream>
#include <vector>
bool isCharsEqual(std::string);
int main()
{
    unsigned rowCount, columnCount;
    std::string** matrix;
    std::vector<unsigned> columnsWithEqualDigitsNums_indexes;
    std::cin >> rowCount >> columnCount;
    matrix = new std::string * [rowCount];
    for (unsigned i = 0; i < rowCount; i++)
    {
        matrix[i] = new std::string[columnCount];
        for (unsigned j = 0; j < columnCount; j++)
            std::cin >> matrix[i][j];
    }
    for (unsigned j = 0; j < columnCount; j++)
        for (unsigned i = 0; i < rowCount; i++)
            if (isCharsEqual(matrix[i][j]))
            {
                columnsWithEqualDigitsNums_indexes.push_back(j + 1);
                break;
            }
    for (auto el : columnsWithEqualDigitsNums_indexes)
        std::cout << el << " ";
    return 0;
}
bool isCharsEqual(std::string str)
{
    for (int i = 1; i < str.size(); i++)
        if (str[i] != str[i - 1])
            return false;
    return true;
}
