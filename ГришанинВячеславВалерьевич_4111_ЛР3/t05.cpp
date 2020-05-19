// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 5. Если среди элементов матрицы есть хотя бы одно число Фибоначчи, повернуть все ее элементы на 90 градусов по часовой стрелке.

// Предположим, что под "...повернуть все ее элементы на 90 градусов по часовой стрелке." имеется в виду такое преобразование
// которое преобразует матрицу
// | 11 12 13 |   | 21 11 |
// | 21 22 23 | в | 22 12 |
//                | 23 13 |
// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.
#include <iostream>
bool isFibonacci(int);
struct Matrix
{
    int rowCount, columnCount;
    int** ptr;
    void reservePtr()
    {
        ptr = new int* [rowCount];
        for (int i = 0; i < rowCount; i++)
            ptr[i] = new int[columnCount];
    }
    void destroyPtr()
    {
        for (int i = 0; i < rowCount; i++)
            delete[] ptr[i];
        delete[] ptr;
        ptr = NULL;
    }
};
int main()
{
    Matrix matrix;
    bool hasFibonacciNum = false;
    std::cin >> matrix.rowCount >> matrix.columnCount;
    matrix.reservePtr();
    for (unsigned i = 0; i < matrix.rowCount; i++)
        for (unsigned j = 0, iter = 0; j < matrix.columnCount; j++, iter = 0)
        {
            std::cin >> matrix.ptr[i][j];
            if (!hasFibonacciNum and isFibonacci(matrix.ptr[i][j]))
                hasFibonacciNum = true;
        }
    if(hasFibonacciNum)
    {
        Matrix rAnglRotatedMatrix;
        rAnglRotatedMatrix.rowCount = matrix.columnCount;
        rAnglRotatedMatrix.columnCount = matrix.rowCount;
        rAnglRotatedMatrix.reservePtr();
        for (unsigned i = 0; i < matrix.rowCount; i++)
            for (unsigned j = 0; j < matrix.columnCount; j++)
                rAnglRotatedMatrix.ptr[j][rAnglRotatedMatrix.columnCount - 1 - i] = matrix.ptr[i][j];
        matrix.destroyPtr();
        matrix.ptr = rAnglRotatedMatrix.ptr;
        rAnglRotatedMatrix.ptr = NULL;
        matrix.rowCount = rAnglRotatedMatrix.rowCount;
        matrix.columnCount = rAnglRotatedMatrix.columnCount;
    }
    for (unsigned i = 0; i < matrix.rowCount; i++)
    {
        for (unsigned j = 0; j < matrix.columnCount; j++)
            std::cout << matrix.ptr[i][j] << " ";
        std::cout << std::endl;
    }
    return 0;
}
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
