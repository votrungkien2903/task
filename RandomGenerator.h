#pragma once
#include <random>

#include "Generator.h"

/// Генератор случайного заполнения: целые числа из отрезка [minValue, maxValue].
class RandomGenerator : public Generator {
public:
    /// Конструктор: границы диапазона. Бросает std::invalid_argument, если minValue > maxValue.
    RandomGenerator(int minValue, int maxValue);

    /// Заполняет матрицу случайными числами.
    void Fill(Matrix& matrix) override;

private:
    std::mt19937 engine_;
    std::uniform_int_distribution<int> distribution_;
};
