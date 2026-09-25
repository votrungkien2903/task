#pragma once

#include "Exercise.h"

template <typename T>
class Task2 : public Exercise<T>
{
public:
    // Создает объект задания Task2.
    Task2(const Matrix<T>& matrix, Generator<T>* generator);

    // Вставляет нулевую строку перед строками,
    // первый элемент которых делится на 3.
    void solve() override;
};


// Создает объект задания Task2.
template <typename T>
Task2<T>::Task2(const Matrix<T>& matrix, Generator<T>* generator)
    : exercise<T>(matrix, generator)
{
}


// Вставляет нулевую строку перед строками,
// первый элемент которых делится на 3.
template <typename T>
void Task2<T>::solve()
{
    // Если матрица пустая, выполнять нечего.
    if (this->matrix.getRows() == 0 || this->matrix.getCols() == 0)
    {
        return;
    }

    // Сохраняем исходное количество строк,
    // чтобы не проверять добавленные нулевые строки повторно.
    const size_t originalRows = this->matrix.getRows();

    // Количество уже добавленных строк.
    size_t insertedRows = 0;

    for (size_t i = 0; i < originalRows; ++i)
    {
        // Получаем индекс текущей строки с учетом ранее вставленных строк.
        size_t currentIndex = i + insertedRows;

        // Проверяем первый элемент строки.
        if (this->matrix[currentIndex][0] % 3 == 0)
        {
            // Создаем строку, состоящую из нулей.
            std::vector<T> zeroRow(
                this->matrix.getCols(),
                T{}
            );

            // Вставляем нулевую строку перед текущей строкой.
            this->matrix.insertRow(currentIndex, zeroRow);

            // Увеличиваем количество добавленных строк.
            ++insertedRows;
        }
    }
}