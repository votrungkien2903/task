#pragma once

#include "generator.h"

template <typename T>
class Constant : public Generator<T>
{
private:
    // Значение, которое будет возвращать генератор.
    T value;

public:
    // Создает генератор с заданным постоянным значением.
    explicit Constant(const T& value);

    // Возвращает постоянное значение.
    T generate() override;
};


// Создает генератор с заданным постоянным значением.
template <typename T>
Constant<T>::Constant(const T& value)
    : value(value)
{
}


// Возвращает постоянное значение.
template <typename T>
T Constant<T>::generate()
{
    return value;
}
