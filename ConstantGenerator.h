#pragma once
#include "Generator.h"

/// Генератор-константа: заполняет все элементы матрицы одним значением.
class ConstantGenerator : public Generator {
public:
    /// Конструктор: значение, которым будут заполнены элементы.
    explicit ConstantGenerator(int value);

    /// Заполняет матрицу константой.
    void Fill(Matrix& matrix) override;

private:
    int value_;
};
