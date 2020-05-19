// Лабораторная работа № 3
// Двумерные массивы
// Ввести размер прямоугольной матрицы и значения ее элементов.
// 12. Продублировать строки матрицы, являющиеся перестановкой элементов чисел от 1 до N.
/*
  In reply to Нина Викторовна Комлева
  Re: Практическое занятие. Подгруппа 1
  от Арина Перепелкина - Среда, 13 Май 2020, 09:11
  объясните, пожалуйста, задачу 12 из ЛР 3.
  Текст задачи "Продублировать строки матрицы, являющиеся перестановкой элементов чисел от 1 до N. "
  Что значит строки, являющиеся перестановкой? Можно, пожалуйста пример, что дано и что получится в итоге. А то как то совсем не понятно
  Изображение пользователя Нина Викторовна Комлева
  In reply to Арина Перепелкина
  Re: Практическое занятие. Подгруппа 1
  от Нина Викторовна Комлева - Среда, 13 Май 2020, 09:26
  Перестановкой из n элементов называется такая последовательность из n чисел, в которую каждое из чисел от 1 до n входит по одному разу.
  Например, перестановка из 5 чисел: 2, 5, 1, 4, 3
  или 4, 3, 5, 1, 2
  In reply to Нина Викторовна Комлева
  Re: Практическое занятие. Подгруппа 1
  от Нина Викторовна Комлева - Среда, 13 Май 2020, 09:27
  Продублировать значит повторить такую строку дважды, количество строк матрицы увеличится и это надо предусмотреть

  Лабораторное занятие. Подгруппа 1
  от Нина Викторовна Комлева - Понедельник, 18 Май 2020, 13:16
  Уважаемые студенты!
  Сегодня на занятии продолжаем выполнение Лабораторной работы №3 на двумерные массивы, а кто уже справился с этим заданием приступает к выполнению Лабораторной работы №4 на строки.
  Обращаю Ваше внимание, что в задании ЛР3 удалить строки (столбцы) матрицы означает подтянуть к началу те строки (столбцы) которые надо оставить.
  Продублировать строки (столбцы) матрицы означает повторить строку (столбец) непосредственно следом за данной строкой (столбцом).
  Прошу всех отметить свое присутствие на занятии. Если возникнут вопросы задавайте.
*/

// В задании нет информации, что подразумевается под "N", предположим, что под этим
// имеется в виду ввведенное после размеров и значений матрицы значение.
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
void fillSetWithNumsfrom1toN(std::set<int>&, int);
void dublicateMatrixRow(Matrix& matrix, int rowIndex);
int main()
{
    Matrix matrix;
    int n;
    std::set<int> from1toNset;
    std::cin >> matrix.rowCount >> matrix.columnCount;
    matrix.reservePtr();
    for (unsigned i = 0; i < matrix.rowCount; i++)
        for (unsigned j = 0; j < matrix.columnCount; j++)
            std::cin >> matrix.ptr[i][j];
    std::cin >> n;
    for (unsigned i = 0; i < matrix.rowCount; i++)
    {
        fillSetWithNumsfrom1toN(from1toNset, n);
        for (unsigned j = 0; j < matrix.columnCount; j++)
            if (from1toNset.find(matrix.ptr[i][j]) != from1toNset.end())
                from1toNset.erase(matrix.ptr[i][j]);
            else
                goto NEXT_ROW; // CONTINUE_OUTER_FOR_LABEL
        dublicateMatrixRow(matrix, i);
        ++i;
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
void fillSetWithNumsfrom1toN(std::set<int>& set, int n)
{
    set.clear();
    if (n > 0)
        for (int i = 1; i <= n; i++)
            set.insert(i);
    else
        for (int i = 1; i >= n; i--)
            set.insert(i);
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
            rowExpandedMatrix.ptr[ei][ej] = matrix.ptr[ei-1][ej];
    matrix.destroyPtr();
    matrix.rowCount = rowExpandedMatrix.rowCount;
    matrix.columnCount = rowExpandedMatrix.columnCount;
    matrix.ptr = rowExpandedMatrix.ptr;
}
