
#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <ostream>
#include <istream>

template <typename T>
class Matrix
{
private:
    // Двумерный массив, хранящий элементы матрицы.
    std::vector<std::vector<T>> data;

public:
    // Конструктор по умолчанию. Создает пустую матрицу.
    Matrix();

    // Конструктор, создающий матрицу заданного размера.
    Matrix(size_t rows, size_t cols);

    // Конструктор, создающий матрицу заданного размера и заполняющий ее значением.
    Matrix(size_t rows, size_t cols, const T& value);

    // Конструктор копирования.
    Matrix(const Matrix& other);

    // Конструктор перемещения.
    Matrix(Matrix&& other) noexcept;

    // Деструктор матрицы.
    ~Matrix();

    // Оператор копирующего присваивания.
    Matrix& operator=(const Matrix& other);

    // Оператор перемещающего присваивания.
    Matrix& operator=(Matrix&& other) noexcept;

    // Возвращает количество строк матрицы.
    size_t getRows() const;

    // Возвращает количество столбцов матрицы.
    size_t getCols() const;

    // Изменяет размер матрицы.
    void resize(size_t rows, size_t cols);

    // Изменяет размер матрицы с заполнением заданным значением.
    void resize(size_t rows, size_t cols, const T& value);

    // Возвращает строку матрицы.
    std::vector<T>& operator[](size_t index);

    // Возвращает константную строку матрицы.
    const std::vector<T>& operator[](size_t index) const;

    // Возвращает строковое представление матрицы.
    std::string toString() const;

    // Вставляет строку перед указанным индексом.
    void insertRow(size_t index, const std::vector<T>& row);

    // Удаляет строку по указанному индексу.
    void removeRow(size_t index);

    // Оператор вывода матрицы в поток.
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);

    // Оператор ввода матрицы из потока.
    template <typename U>
    friend std::istream& operator>>(std::istream& is, Matrix<U>& matrix);
};


// Конструктор по умолчанию. Создает пустую матрицу.
template <typename T>
Matrix<T>::Matrix()
{
}


// Конструктор, создающий матрицу заданного размера.
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    : data(rows, std::vector<T>(cols))
{
}


// Конструктор, создающий матрицу заданного размера и заполняющий ее значением.
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T& value)
    : data(rows, std::vector<T>(cols, value))
{
}


// Конструктор копирования.
template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : data(other.data)
{
}


// Конструктор перемещения.
template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : data(std::move(other.data))
{
}


// Деструктор матрицы.
template <typename T>
Matrix<T>::~Matrix()
{
}


// Оператор копирующего присваивания.
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other)
{
    if (this != &other)
    {
        data = other.data;
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
    }

    return *this;
}


// Возвращает количество строк матрицы.
template <typename T>
size_t Matrix<T>::getRows() const
{
    return data.size();
}


// Возвращает количество столбцов матрицы.
template <typename T>
size_t Matrix<T>::getCols() const
{
    if (data.empty())
    {
        return 0;
    }

    return data[0].size();
}


// Изменяет размер матрицы.
template <typename T>
void Matrix<T>::resize(size_t rows, size_t cols)
{
    data.resize(rows);

    for (auto& row : data)
    {
        row.resize(cols);
    }
}


// Изменяет размер матрицы с заполнением заданным значением.
template <typename T>
void Matrix<T>::resize(size_t rows, size_t cols, const T& value)
{
    data.resize(rows);

    for (auto& row : data)
    {
        row.resize(cols, value);
    }
}


// Возвращает строку матрицы.
template <typename T>
std::vector<T>& Matrix<T>::operator[](size_t index)
{
    return data.at(index);
}


// Возвращает константную строку матрицы.
template <typename T>
const std::vector<T>& Matrix<T>::operator[](size_t index) const
{
    return data.at(index);
}


// Возвращает строковое представление матрицы.
template <typename T>
std::string Matrix<T>::toString() const
{
    std::ostringstream output;

    for (size_t i = 0; i < getRows(); ++i)
    {
        for (size_t j = 0; j < getCols(); ++j)
        {
            output << data[i][j];

            if (j + 1 < getCols())
            {
                output << ' ';
            }
        }

        if (i + 1 < getRows())
        {
            output << '\n';
        }
    }

    return output.str();
}


// Вставляет строку перед указанным индексом.
template <typename T>
void Matrix<T>::insertRow(size_t index, const std::vector<T>& row)
{
    if (index > getRows())
    {
        throw std::out_of_range("Invalid row index");
    }

    if (getCols() != row.size())
    {
        throw std::invalid_argument("Invalid row size");
    }

    data.insert(data.begin() + index, row);
}


// Удаляет строку по указанному индексу.
template <typename T>
void Matrix<T>::removeRow(size_t index)
{
    if (index >= getRows())
    {
        throw std::out_of_range("Invalid row index");
    }

    data.erase(data.begin() + index);
}


// Оператор вывода матрицы в поток.
template <typename U>
std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix)
{
    os << matrix.toString();
    return os;
}


// Оператор ввода матрицы из потока.
template <typename U>
std::istream& operator>>(std::istream& is, Matrix<U>& matrix)
{
    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (size_t j = 0; j < matrix.getCols(); ++j)
        {
            is >> matrix.data[i][j];
        }
    }

    return is;
}