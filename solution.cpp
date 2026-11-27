#include <iostream>
#include <stdexcept>

#include "matrix.h"
#include "ManualGenerator.h"
#include "RandomGenerator.h"
#include "task1.h"
#include "task2.h"

enum class FillMethod
{
    Random = 1,
    Manual = 2
};

int main()
{
    std::size_t rows = 0;
    std::size_t cols = 0;

    std::cout << "Введите количество строк и столбцов матрицы: ";

    if (!(std::cin >> rows >> cols) || rows == 0 || cols == 0)
    {
        std::cerr << "Ошибка: размеры матрицы должны быть положительными числами.\n";
        return 1;
    }

    Matrix<int> matrix(rows, cols);

    int choice = 0;
    std::cout << "Выберите способ заполнения матрицы:\n";
    std::cout << "1. Случайные числа (Random)\n";
    std::cout << "2. Ручной ввод (Manual)\n";
    std::cout << "Ваш выбор: ";

    if (!(std::cin >> choice))
    {
        std::cerr << "Ошибка: введите номер способа заполнения.\n";
        return 1;
    }

    try
    {
        switch (static_cast<FillMethod>(choice))
        {
        case FillMethod::Random:
        {
            int minValue = 0;
            int maxValue = 0;

            std::cout << "Введите минимальное и максимальное значения: ";

            if (!(std::cin >> minValue >> maxValue))
            {
                std::cerr << "Ошибка ввода диапазона случайных чисел.\n";
                return 1;
            }

            RandomGenerator generator(minValue, maxValue);
            matrix.fill(generator);
            break;
        }
        case FillMethod::Manual:
        {
            ManualGenerator<int> generator;
            std::cout << "Введите элементы матрицы (" << rows << "x" << cols << "):\n";
            matrix.fill(generator);
            break;
        }
        default:
            std::cerr << "Ошибка: выберите один из предложенных способов.\n";
            return 1;
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    std::cout << "\nИсходная матрица:\n" << matrix << "\n\n";

    // Выполняем первое задание над копией исходной матрицы.
    Task1<int> task1(matrix);
    task1.solve();
    std::cout << "Результат Task1:\n" << task1.getMatrix() << "\n\n";

    // Выполняем второе задание над другой копией исходной матрицы.
    Task2<int> task2(matrix);
    task2.solve();
    std::cout << "Результат Task2:\n" << task2.getMatrix() << '\n';

    return 0;
}
