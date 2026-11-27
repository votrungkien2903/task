#pragma once

#include "matrix.h"

template <typename T>
class Generator
{
public:
    // Виртуальный деструктор базового класса генераторов.
    virtual ~Generator() = default;

    // Возвращает одно значение, созданное генератором.
    virtual T generate() = 0;
};
