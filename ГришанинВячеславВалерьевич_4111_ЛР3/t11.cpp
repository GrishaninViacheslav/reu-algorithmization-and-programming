// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 11. Удалить столбцы матрицы, где есть хотя бы одно совершенное число.

// В тексте задания нет уточнения, что значит "удалить столбец массива",
// предположим, что под этим имеется в виду освобождение блока памяти в
// котором хранятся значения столбца и обнуление указателя на эту столбец.
// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.
#include <iostream>
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
void transposeMatrix(Matrix&);
bool isNumPerfect(int);
int main()
{
    Matrix matrix;
    std::cin >> matrix.rowCount >> matrix.columnCount;
    matrix.reservePtr();
    for (unsigned i = 0; i < matrix.rowCount; i++)
        for (unsigned j = 0; j < matrix.columnCount; j++)
            std::cin >> matrix.ptr[i][j];
    transposeMatrix(matrix);
    for (unsigned i = 0; i < matrix.rowCount; i++)
        for (unsigned j = 0; j < matrix.columnCount; j++)
            if (isNumPerfect(matrix.ptr[i][j]))
            {
                for (unsigned k = i; k < matrix.rowCount - 1; k++)
                    for (unsigned j = 0; j < matrix.columnCount; j++)
                        matrix.ptr[k][j] = matrix.ptr[k + 1][j];
                delete[] matrix.ptr[matrix.rowCount - 1];
                matrix.ptr[matrix.rowCount - 1] = NULL;
                --matrix.rowCount;
                --i;
                break;
            }
    transposeMatrix(matrix);
    for (unsigned i = 0; i < matrix.rowCount; i++)
    {
        for (unsigned j = 0; j < matrix.columnCount; j++)
            std::cout << matrix.ptr[i][j] << " ";
        std::cout << std::endl;
    }
    matrix.destroyPtr();
    return 0;
}
void transposeMatrix(Matrix& matrix)
{
    Matrix transposedMatrix;
    transposedMatrix.rowCount = matrix.columnCount;
    transposedMatrix.columnCount = matrix.rowCount;
    transposedMatrix.reservePtr();
    for (unsigned i = 0; i < transposedMatrix.rowCount; i++)
        for (unsigned j = 0; j < transposedMatrix.columnCount; j++)
            transposedMatrix.ptr[i][j] = matrix.ptr[j][i];
    matrix.destroyPtr();
    matrix.rowCount = transposedMatrix.rowCount;
    matrix.columnCount = transposedMatrix.columnCount;
    matrix.ptr = transposedMatrix.ptr;
}
bool isNumPerfect(int num)
{
    if (num == 0)
        return false;
    int sum = 0;
    for (int i = 1; i < num; i++)
        if (num % i == 0)
            sum += i;
    return sum == num;
}
