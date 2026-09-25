#pragma once

#include "generator.h"
#include <random>

class RandomGenerator : public Generator<int>
{
private:
    // Минимальное случайное значение.
    int minValue;

    // Максимальное случайное значение.
    int maxValue;

public:
    // Создает генератор случайных чисел.
    RandomGenerator(int minValue, int maxValue);

    // Заполняет матрицу случайными числами.
    void generate(Matrix<int>& matrix) override;
};


// Создает генератор случайных чисел.
inline RandomGenerator::RandomGenerator(
    int minValue,
    int maxValue
)
    : minValue(minValue),
    maxValue(maxValue)
{
}


// Заполняет матрицу случайными числами.
inline void RandomGenerator::generate(Matrix<int>& matrix)
{
    // Создаем генератор случайных чисел.
    std::random_device rd;
    std::mt19937 generator(rd());

    // Задаем диапазон случайных чисел.
    std::uniform_int_distribution<int> distribution(
        minValue,
        maxValue
    );

    // Перебираем все строки матрицы.
    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        // Перебираем все элементы строки.
        for (size_t j = 0; j < matrix.getCols(); ++j)
        {
            // Записываем случайное число.
            matrix[i][j] = distribution(generator);
        }
    }
}