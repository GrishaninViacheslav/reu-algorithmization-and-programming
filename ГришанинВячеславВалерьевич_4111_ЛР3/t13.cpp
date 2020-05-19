// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 13.  Продублировать столбцы матрицы, элементы которых являются перестановкой элементов последнего  столбца.
/*
  Лабораторное занятие. Подгруппа 1
  от Нина Викторовна Комлева - Понедельник, 18 Май 2020, 13:16
  Уважаемые студенты!
  Сегодня на занятии продолжаем выполнение Лабораторной работы №3 на двумерные массивы, а кто уже справился с этим заданием приступает к выполнению Лабораторной работы №4 на строки.
  Обращаю Ваше внимание, что в задании ЛР3 удалить строки (столбцы) матрицы означает подтянуть к началу те строки (столбцы) которые надо оставить.
  Продублировать строки (столбцы) матрицы означает повторить строку (столбец) непосредственно следом за данной строкой (столбцом).
  Прошу всех отметить свое присутствие на занятии. Если возникнут вопросы задавайте.
*/

// В тексте задания нет информации о том какие значения вводятся. Предположим, что вводятся
// целые числа в диапазоне [INT_MIN; INT_MAX]. Неопределенно как вводятся значения элементов матрицы,
// предположим что ввод происходит последовательно по строкам.

#include <iostream>
#include <set>
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
void fillSetWithArrVals(std::set<int>&, int*, int);
void dublicateMatrixRow(Matrix& matrix, int rowIndex);
void transposeMatrix(Matrix&);
int main()
{
    Matrix matrix;
    std::set<int> matrixLastColumnValsSet;
    int* matrixLastColumnVals;
    std::cin >> matrix.rowCount >> matrix.columnCount;
    matrixLastColumnVals = new int[matrix.rowCount];
    matrix.reservePtr();
    for (unsigned i = 0, k = 0; i < matrix.rowCount; i++)
        for (unsigned j = 0; j < matrix.columnCount; j++)
        {
            std::cin >> matrix.ptr[i][j];
            if (j == matrix.columnCount - 1)
                matrixLastColumnVals[k++] = matrix.ptr[i][j];
        }
    for (unsigned j = 0; j < matrix.columnCount; j++)
    {
        fillSetWithArrVals(matrixLastColumnValsSet, matrixLastColumnVals, matrix.rowCount);
        for (unsigned i = 0; i < matrix.rowCount; i++)
            if (matrixLastColumnValsSet.find(matrix.ptr[i][j]) != matrixLastColumnValsSet.end())
                matrixLastColumnValsSet.erase(matrix.ptr[i][j]);
            else
                goto NEXT_ROW; // CONTINUE_OUTER_FOR_LABEL
        transposeMatrix(matrix);
        dublicateMatrixRow(matrix, j);
        transposeMatrix(matrix);
        ++j;
        NEXT_ROW:;
    }
    for (unsigned i = 0; i < matrix.rowCount; i++)
    {
        for (unsigned j = 0; j < matrix.columnCount; j++)
            std::cout << matrix.ptr[i][j] << " ";
        std::cout << std::endl;
    }
    return 0;
}
void fillSetWithArrVals(std::set<int>& set, int* arr, int arrSize)
{
    set.clear();
    for(int i = 0; i < arrSize; i++)
        set.insert(arr[i]);
}
void dublicateMatrixRow(Matrix& matrix, int rowIndex)
{
    Matrix rowExpandedMatrix;
    rowExpandedMatrix.rowCount = matrix.rowCount + 1;
    rowExpandedMatrix.columnCount = matrix.columnCount;
    rowExpandedMatrix.reservePtr();
    for (unsigned ei = 0; ei <= rowIndex; ei++)
        for (unsigned ej = 0; ej < matrix.columnCount; ej++)
            rowExpandedMatrix.ptr[ei][ej] = matrix.ptr[ei][ej];
    for (unsigned ej = 0; ej < matrix.columnCount; ej++)
        rowExpandedMatrix.ptr[rowIndex + 1][ej] = matrix.ptr[rowIndex][ej];
    for (unsigned ei = rowIndex + 2; ei < rowExpandedMatrix.rowCount; ei++)
        for (unsigned ej = 0; ej < matrix.columnCount; ej++)
            rowExpandedMatrix.ptr[ei][ej] = matrix.ptr[ei - 1][ej];
    matrix.destroyPtr();
    matrix.rowCount = rowExpandedMatrix.rowCount;
    matrix.columnCount = rowExpandedMatrix.columnCount;
    matrix.ptr = rowExpandedMatrix.ptr;
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
