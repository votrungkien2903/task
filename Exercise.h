#pragma once

#include "matrix.h"
#include "generator.h"

template <typename T>
class Exercise
{
protected:
    // Матрица, над которой выполняется задание.
    Matrix<T> matrix;

    // Генератор, используемый для заполнения матрицы.
    Generator<T>* generator;

public:
    // Создает упражнение с заданной матрицей и генератором.
    Exercise(const Matrix<T>& matrix, Generator<T>* generator);

    // Виртуальный деструктор базового класса Exercise.
    virtual ~Exercise() = default;

    // Выполняет конкретное задание.
    virtual void solve() = 0;

    // Возвращает матрицу задания.
    const Matrix<T>& getMatrix() const;
};


// Создает упражнение с заданной матрицей и генератором.
template <typename T>
Exercise<T>::Exercise(const Matrix<T>& matrix, Generator<T>* generator)
    : matrix(matrix), generator(generator)
{
}


// Возвращает матрицу задания.
template <typename T>
const Matrix<T>& Exercise<T>::getMatrix() const
{
    return matrix;
}