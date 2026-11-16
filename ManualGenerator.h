#pragma once

#include "generator.h"

#include <istream>
#include <vector>

template <typename T>
class ManualGenerator : public Generator<T>
{
public:
    // Заполняет матрицу значениями, введенными пользователем.
    bool generate(Matrix<T>& matrix, std::istream& input);
};


// Заполняет матрицу значениями, введенными пользователем.
template <typename T>
bool ManualGenerator<T>::generate(Matrix<T>& matrix, std::istream& input)
{
    // Сначала считываем данные во временную матрицу.
    // Исходная матрица изменится только при полном успешном вводе.
    std::vector<std::vector<T>> values(
        matrix.getRows(),
        std::vector<T>(matrix.getCols())
    );

    for (std::size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (std::size_t j = 0; j < matrix.getCols(); ++j)
        {
            if (!(input >> values[i][j]))
            {
                return false;
            }
        }
    }

    // Переносим считанные значения в матрицу.
    for (std::size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (std::size_t j = 0; j < matrix.getCols(); ++j)
        {
            matrix[i][j] = values[i][j];
        }
    }

    return true;
}
