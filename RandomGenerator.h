#pragma once

#include "generator.h"

#include <random>
#include <stdexcept>

class RandomGenerator : public Generator<int>
{
private:
    // Генератор псевдослучайных чисел.
    std::mt19937 engine;

    // Равномерное распределение случайных чисел.
    std::uniform_int_distribution<int> distribution;

public:
    // Создает генератор случайных чисел в заданном диапазоне.
    RandomGenerator(const int minValue, const int maxValue);

    // Возвращает одно случайное число.
    int generate() override;
};


// Создает генератор случайных чисел в заданном диапазоне.
inline RandomGenerator::RandomGenerator(const int minValue, const int maxValue)
    : engine(std::random_device{}()), distribution()
{
    if (minValue > maxValue)
    {
        throw std::invalid_argument("Минимальное значение больше максимального");
    }

    distribution = std::uniform_int_distribution<int>(minValue, maxValue);
}


// Возвращает одно случайное число.
inline int RandomGenerator::generate()
{
    return distribution(engine);
}
