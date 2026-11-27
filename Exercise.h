#pragma once

#include "matrix.h"

template <typename T>
class Exercise
{
protected:
    // Матрица, над которой выполняется задание.
    Matrix<T> matrix;

public:
    // Создает упражнение с копией заданной матрицы.
    explicit Exercise(const Matrix<T>& matrix);

    // Виртуальный деструктор базового класса.
    virtual ~Exercise() = default;

    // Выполняет конкретное задание.
    virtual void solve() = 0;

    // Возвращает матрицу задания.
    const Matrix<T>& getMatrix() const;
};


// Создает упражнение с копией заданной матрицы.
template <typename T>
Exercise<T>::Exercise(const Matrix<T>& matrix)
    : matrix(matrix)
{
}


// Возвращает матрицу задания.
template <typename T>
const Matrix<T>& Exercise<T>::getMatrix() const
{
    return matrix;
}
