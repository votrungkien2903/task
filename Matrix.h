#pragma once
#include <cstddef>
#include <vector>

/// Прямоугольная матрица целых чисел.
/// В больнице хранит матрицу связей: строки - медицинские работники,
/// столбцы - пациенты, ненулевой элемент означает «работник наблюдает пациента».
class Matrix {
public:
    /// Создаёт матрицу rows x cols, заполненную нулями.
    /// Бросает std::invalid_argument, если rows или cols равны нулю.
    Matrix(std::size_t rows, std::size_t cols);

    /// Возвращает количество строк.
    std::size_t GetRows() const;

    /// Возвращает количество столбцов.
    std::size_t GetCols() const;

    /// Возвращает элемент (row, col). Бросает std::out_of_range при неверных индексах.
    int Get(std::size_t row, std::size_t col) const;

    /// Записывает значение в элемент (row, col). Бросает std::out_of_range при неверных индексах.
    void Set(std::size_t row, std::size_t col, int value);

private:
    /// Проверяет индексы; бросает std::out_of_range, если они вне матрицы.
    void CheckIndex(std::size_t row, std::size_t col) const;

    std::size_t rows_;
    std::size_t cols_;
    std::vector<int> data_;
};
