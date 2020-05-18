// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 9. Определить сумму тех элементов матрицы,
// все цифры в которых упорядочены строго по возрастанию или строго по убыванию.

// В тексте нет информации о том в какой системе счсиления представляются числа,
// предположим, что все числа в матрице представленны в десятичной системе счисления.
// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.

#include <iostream>
#include <cmath>
bool isDigitsScending(int);
int main()
{
    unsigned rowCount, columnCount;
    int** matrix;
    int sum = 0;
    std::cin >> rowCount >> columnCount;
    matrix = new int* [rowCount];
    for (unsigned i = 0; i < rowCount; i++)
    {
        matrix[i] = new int[columnCount];
        for (unsigned j = 0; j < columnCount; j++)
        {
            std::cin >> matrix[i][j];
            if (isDigitsScending(matrix[i][j]))
                sum += matrix[i][j];
        }
    }
    std::cout << sum;
    return 0;
}
bool isDigitsScending(int num) // if i digit > i-1 digit or i digit < i-1 digit then true else false
{
    bool isAscending;
    if(abs(num) < 10)
        return false;
    else if (num % 10 > num / 10 % 10)
        isAscending = true;
    else if (num % 10 < num / 10 % 10)
        isAscending = false;
    else
        return false;
    while ((num /= 10) > 9)
        if ((isAscending && num % 10 <= num / 10 % 10) || (!isAscending && num % 10 >= num / 10 % 10))
            return false;
    return true;
}
