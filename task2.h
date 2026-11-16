#pragma once

#include <vector>
#include "Exercise.h"

template <typename T>
class Task2 : public Exercise<T>
{
public:
    // Создает объект задания Task2.
    explicit Task2(const Matrix<T>& matrix);

    // Вставляет нулевую строку перед строками,
    // первый элемент которых делится на 3.
    void solve() override;
};


// Создает объект задания Task2.
template <typename T>
Task2<T>::Task2(const Matrix<T>& matrix)
    : Exercise<T>(matrix)
{
}


// Вставляет нулевую строку перед строками,
// первый элемент которых делится на 3.
template <typename T>
void Task2<T>::solve()
{
    const std::size_t originalRows = this->matrix.getRows();
    const std::size_t cols = this->matrix.getCols();

    // Если в матрице нет строк или столбцов, вставлять нечего.
    if (originalRows == 0 || cols == 0)
    {
        return;
    }

    // Формируем новый набор строк, не изменяя интерфейс класса Matrix.
    std::vector<std::vector<T>> resultRows;
    resultRows.reserve(originalRows * 2);

    for (std::size_t i = 0; i < originalRows; ++i)
    {
        // Добавляем нулевую строку перед подходящей исходной строкой.
        if (this->matrix[i][0] % 3 == 0)
        {
            resultRows.emplace_back(cols, T{});
        }

        resultRows.push_back(this->matrix[i]);
    }

    // Создаем матрицу нужного размера и переносим в нее строки.
    Matrix<T> result(resultRows.size(), cols);

    for (std::size_t i = 0; i < resultRows.size(); ++i)
    {
        for (std::size_t j = 0; j < cols; ++j)
        {
            result[i][j] = resultRows[i][j];
        }
    }

    this->matrix = std::move(result);
}
