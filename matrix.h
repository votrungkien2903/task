#pragma once

#include <cstddef>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class Matrix
{
private:
    // Двумерный массив, хранящий элементы матрицы.
    std::vector<std::vector<T>> data;

    // Количество строк матрицы.
    std::size_t rows;

    // Количество столбцов матрицы.
    std::size_t cols;

public:
    // Создает пустую матрицу.
    Matrix();

    // Создает матрицу заданного размера.
    Matrix(const std::size_t rows, const std::size_t cols);

    // Конструктор копирования.
    Matrix(const Matrix& other);

    // Конструктор перемещения.
    Matrix(Matrix&& other) noexcept;

    // Оператор копирующего присваивания.
    Matrix& operator=(const Matrix& other);

    // Оператор перемещающего присваивания.
    Matrix& operator=(Matrix&& other) noexcept;

    // Возвращает количество строк матрицы.
    std::size_t getRows() const;

    // Возвращает количество столбцов матрицы.
    std::size_t getCols() const;

    // Возвращает строку матрицы по индексу.
    std::vector<T>& operator[](const std::size_t index);

    // Возвращает константную строку матрицы по индексу.
    const std::vector<T>& operator[](const std::size_t index) const;

    // Возвращает строковое представление матрицы.
    std::string toString() const;

    // Выводит матрицу в поток.
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);

    // Считывает элементы матрицы из потока.
    template <typename U>
    friend std::istream& operator>>(std::istream& is, Matrix<U>& matrix);
};


// Создает пустую матрицу.
template <typename T>
Matrix<T>::Matrix()
    : rows(0), cols(0)
{
}


// Создает матрицу заданного размера.
template <typename T>
Matrix<T>::Matrix(const std::size_t rows, const std::size_t cols)
    : data(rows, std::vector<T>(cols)), rows(rows), cols(cols)
{
}


// Конструктор копирования.
template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : data(other.data), rows(other.rows), cols(other.cols)
{
}


// Конструктор перемещения.
template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : data(std::move(other.data)), rows(other.rows), cols(other.cols)
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
std::size_t Matrix<T>::getRows() const
{
    return rows;
}


// Возвращает количество столбцов матрицы.
template <typename T>
std::size_t Matrix<T>::getCols() const
{
    return cols;
}


// Возвращает строку матрицы по индексу.
template <typename T>
std::vector<T>& Matrix<T>::operator[](const std::size_t index)
{
    return data.at(index);
}


// Возвращает константную строку матрицы по индексу.
template <typename T>
const std::vector<T>& Matrix<T>::operator[](const std::size_t index) const
{
    return data.at(index);
}


// Возвращает строковое представление матрицы.
template <typename T>
std::string Matrix<T>::toString() const
{
    std::ostringstream output;

    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < cols; ++j)
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


// Выводит матрицу в поток.
template <typename U>
std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix)
{
    return os << matrix.toString();
}


// Считывает элементы матрицы из потока.
template <typename U>
std::istream& operator>>(std::istream& is, Matrix<U>& matrix)
{
    for (std::size_t i = 0; i < matrix.rows; ++i)
    {
        for (std::size_t j = 0; j < matrix.cols; ++j)
        {
            if (!(is >> matrix.data[i][j]))
            {
                return is;
            }
        }
    }

    return is;
}
