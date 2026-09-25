#pragma once

#include "generator.h"

template <typename T>
class ZeroGenerator : public Generator<T>
{
public:
    // Заполняет всю матрицу нулевыми значениями.
    void generate(Matrix<T>& matrix) override;
};


// Заполняет всю матрицу нулевыми значениями.
template <typename T>
void ZeroGenerator<T>::generate(Matrix<T>& matrix)
{
    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (size_t j = 0; j < matrix.getCols(); ++j)
        {
            matrix[i][j] = T{};
        }
    }
}