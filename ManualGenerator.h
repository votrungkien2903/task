#pragma once

#include "generator.h"

#include <iostream>
#include <istream>
#include <vector>

template <typename T>
class ManualGenerator : public Generator<T>
{
public:
    // Заполняет матрицу данными из стандартного потока ввода.
    void generate(Matrix<T>& matrix) override;

    // Заполняет матрицу данными из указанного потока.
    bool generate(Matrix<T>& matrix, std::istream& input);
};


// Заполняет матрицу данными из стандартного потока ввода.
template <typename T>
void ManualGenerator<T>::generate(Matrix<T>& matrix)
{
    generate(matrix, std::cin);
}


// Заполняет матрицу данными из указанного потока.
template <typename T>
bool ManualGenerator<T>::generate(Matrix<T>& matrix, std::istream& input)
{
    // Сначала считываем данные во временный массив.
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
