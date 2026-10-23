
#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <ostream>
#include <istream>
#include <utility>

template <typename T>
class Matrix
{
private:
    // Двумерный массив, хранящий элементы матрицы.
    std::vector<std::vector<T>> data;

    // Количество строк матрицы.
    size_t rows = 0;

    // Количество столбцов матрицы.
    size_t cols = 0;

public:
    // Конструктор по умолчанию.
    Matrix();

    // Конструктор, создающий матрицу заданного размера.
    Matrix(const size_t rows, const size_t cols);

    // Конструктор копирования.
    Matrix(const Matrix& other);

    // Конструктор перемещения.
    Matrix(Matrix&& other) noexcept;

    // Оператор копирующего присваивания.
    Matrix& operator=(const Matrix& other);

    // Оператор перемещающего присваивания.
    Matrix& operator=(Matrix&& other) noexcept;

    // Возвращает количество строк матрицы.
    size_t getRows() const;

    // Возвращает количество столбцов матрицы.
    size_t getCols() const;

    // Возвращает строку матрицы.
    std::vector<T>& operator[](const size_t index);

    // Возвращает константную строку матрицы.
    const std::vector<T>& operator[](const size_t index) const;

    // Возвращает строковое представление матрицы.
    std::string toString() const;

    // Оператор вывода матрицы в поток.
    template <typename U>
    friend std::ostream& operator<<(
        std::ostream& os,
        const Matrix<U>& matrix
        );

    // Оператор ввода матрицы из потока.
    template <typename U>
    friend std::istream& operator>>(
        std::istream& is,
        Matrix<U>& matrix
        );
};


// Конструктор по умолчанию.
template <typename T>
Matrix<T>::Matrix()
    : rows(0), cols(0)
{
}


// Конструктор, создающий матрицу заданного размера.
template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols)
    : data(rows, std::vector<T>(cols)),
    rows(rows),
    cols(cols)
{
}


// Конструктор копирования.
template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : data(other.data),
    rows(other.rows),
    cols(other.cols)
{
}


// Конструктор перемещения.
template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : data(std::move(other.data)),
    rows(other.rows),
    cols(other.cols)
{
    other.rows = 0;
    other.cols = 0;
}


// Оператор копирующего присваивания.
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other)
{
    if (this != &other)
    {
        data = other.data;
        rows = other.rows;
        cols = other.cols;
    }

    return *this;
}


// Оператор перемещающего присваивания.
template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
{
    if (this != &other)
    {
        data = std::move(other.data);
        rows = other.rows;
        cols = other.cols;

        other.rows = 0;
        other.cols = 0;
    }

    return *this;
}


// Возвращает количество строк матрицы.
template <typename T>
size_t Matrix<T>::getRows() const
{
    return rows;
}


// Возвращает количество столбцов матрицы.
template <typename T>
size_t Matrix<T>::getCols() const
{
    return cols;
}


// Возвращает строку матрицы.
template <typename T>
std::vector<T>& Matrix<T>::operator[](const size_t index)
{
    return data.at(index);
}


// Возвращает константную строку матрицы.
template <typename T>
const std::vector<T>& Matrix<T>::operator[](const size_t index) const
{
    return data.at(index);
}


// Возвращает строковое представление матрицы.
template <typename T>
std::string Matrix<T>::toString() const
{
    std::ostringstream output;

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            output << data[i][j];

            if (j + 1 < cols)
            {
                output << ' ';
            }
        }

        if (i + 1 < rows)
        {
            output << '\n';
        }
    }

    return output.str();
}


// Оператор вывода матрицы в поток.
template <typename U>
std::ostream& operator<<(
    std::ostream& os,
    const Matrix<U>& matrix
    )
{
    os << matrix.toString();
    return os;
}


// Оператор ввода матрицы из потока.
template <typename U>
std::istream& operator>>(
    std::istream& is,
    Matrix<U>& matrix
    )
{
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.cols; ++j)
        {
            is >> matrix.data[i][j];
        }
    }

    return is;
}
