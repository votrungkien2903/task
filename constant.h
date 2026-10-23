#pragma once

#include "generator.h"

template <typename T>
class Constant : public generator<T>
{
private:
    // Значение, которым будет заполнена матрица.
    T value;

public:
    // Создает генератор с заданным постоянным значением.
    explicit Constant(const T& value);

    // Заполняет матрицу постоянным значением.
    void generate(Matrix<T>& matrix) override;
};


// Создает генератор с заданным постоянным значением.
template <typename T>
Constant<T>::Constant(const T& value)
    : value(value)
{
}


// Заполняет матрицу постоянным значением.
template <typename T>
void Constant<T>::generate(Matrix<T>& matrix)
{
    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (size_t j = 0; j < matrix.getCols(); ++j)
        {
            matrix[i][j] = value;
        }
    }
}