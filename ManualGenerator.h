#pragma once

#include "generator.h"

#include <iostream>
#include <istream>
#include <stdexcept>

template <typename T>
class ManualGenerator : public Generator<T>
{
private:
    // Поток, из которого считываются значения.
    std::istream* input;

public:
    // Создает генератор, считывающий значения с клавиатуры.
    ManualGenerator();

    // Создает генератор для указанного потока.
    explicit ManualGenerator(std::istream& input);

    // Считывает и возвращает одно значение.
    T generate() override;
};


// Создает генератор, считывающий значения с клавиатуры.
template <typename T>
ManualGenerator<T>::ManualGenerator()
    : input(&std::cin)
{
}


// Создает генератор для указанного потока.
template <typename T>
ManualGenerator<T>::ManualGenerator(std::istream& input)
    : input(&input)
{
}


// Считывает и возвращает одно значение.
template <typename T>
T ManualGenerator<T>::generate()
{
    T value{};

    if (!(*input >> value))
    {
        throw std::runtime_error("Ошибка ввода элемента матрицы");
    }

    return value;
}
