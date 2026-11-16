#pragma once

#include "generator.h"

#include <random>
#include <stdexcept>

class RandomGenerator : public Generator<int>
{
private:
    // Минимальное случайное значение.
    int minValue;

    // Максимальное случайное значение.
    int maxValue;

public:
    // Создает генератор случайных чисел.
    RandomGenerator(const int minValue, const int maxValue);

    // Заполняет матрицу случайными числами.
    void generate(Matrix<int>& matrix) override;
};


// Создает генератор случайных чисел.
inline RandomGenerator::RandomGenerator(const int minValue, const int maxValue)
    : minValue(minValue), maxValue(maxValue)
{
    if (minValue > maxValue)
    {
        throw std::invalid_argument("Минимальное значение больше максимального");
    }
}


// Заполняет матрицу случайными числами.
inline void RandomGenerator::generate(Matrix<int>& matrix)
{
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<int> distribution(minValue, maxValue);

    for (std::size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (std::size_t j = 0; j < matrix.getCols(); ++j)
        {
            matrix[i][j] = distribution(engine);
        }
    }
}
