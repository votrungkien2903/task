#pragma once

#include "matrix.h"

template <typename T>
class Generator
{
public:
    // Виртуальный деструктор базового класса генераторов.
    virtual ~Generator() = default;

    // Заполняет матрицу согласно конкретному алгоритму.
    virtual void generate(Matrix<T>& matrix) = 0;
};