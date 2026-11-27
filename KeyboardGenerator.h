#pragma once
#include <functional>

#include "Generator.h"

/// Генератор «ввод с клавиатуры».
/// Чтобы библиотека не зависела от потоков ввода-вывода, значения запрашиваются
/// у функции-поставщика, которую передаёт приложение (оно само читает std::cin).
class KeyboardGenerator : public Generator {
public:
    /// Тип поставщика: по позиции (строка, столбец) возвращает вводимое число.
    using ValueSupplier = std::function<int(std::size_t row, std::size_t col)>;

    /// Конструктор. Бросает std::invalid_argument, если supplier пуст.
    explicit KeyboardGenerator(ValueSupplier supplier);

    /// Заполняет матрицу по строкам значениями от поставщика.
    void Fill(Matrix& matrix) override;

private:
    ValueSupplier supplier_;
};
