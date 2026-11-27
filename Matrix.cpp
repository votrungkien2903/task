#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix(std::size_t rows, std::size_t cols) : rows_(rows), cols_(cols), data_(rows * cols, 0) {
    if (rows == 0 || cols == 0) throw std::invalid_argument("Размеры матрицы должны быть положительными");
}

std::size_t Matrix::GetRows() const { return rows_; }

std::size_t Matrix::GetCols() const { return cols_; }

void Matrix::CheckIndex(std::size_t row, std::size_t col) const {
    if (row >= rows_ || col >= cols_) throw std::out_of_range("Индекс выходит за границы матрицы");
}

int Matrix::Get(std::size_t row, std::size_t col) const {
    CheckIndex(row, col);
    return data_[row * cols_ + col];
}

void Matrix::Set(std::size_t row, std::size_t col, int value) {
    CheckIndex(row, col);
    data_[row * cols_ + col] = value;
}
