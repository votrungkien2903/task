#pragma once

#include "Exercise.h"

template <typename T>
class Task1 : public Exercise<T>
{
public:
    // Создает объект задания Task1.
    explicit Task1(const Matrix<T>& matrix);

    // Заменяет максимальный элемент каждой строки нулем.
    void solve() override;
};


// Создает объект задания Task1.
template <typename T>
Task1<T>::Task1(const Matrix<T>& matrix)
    : Exercise<T>(matrix)
{
}


// Заменяет максимальный элемент каждой строки нулем.
template <typename T>
void Task1<T>::solve()
{
    // Для пустой матрицы обработка не требуется.
    if (this->matrix.getRows() == 0 || this->matrix.getCols() == 0)
    {
        return;
    }

    for (std::size_t i = 0; i < this->matrix.getRows(); ++i)
    {
        std::size_t maxIndex = 0;

        for (std::size_t j = 1; j < this->matrix.getCols(); ++j)
        {
            if (this->matrix[i][j] > this->matrix[i][maxIndex])
            {
                maxIndex = j;
            }
        }

        this->matrix[i][maxIndex] = T{};
    }
}
