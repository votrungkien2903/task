#include <iostream>

#include "matrix.h"
#include "ManualGenerator.h"
#include "RandomGenerator.h"
#include "task1.h"
#include "task2.h"

int main()
{
    const std::size_t rows = 4;
    const std::size_t cols = 4;

    Matrix<int> matrix(rows, cols);

    // Предлагаем пользователю выбрать способ заполнения матрицы.
    int choice = 0;
    std::cout << "Выберите способ заполнения матрицы:\n";
    std::cout << "1. Случайные числа (Random)\n";
    std::cout << "2. Ручной ввод (Manual)\n";
    std::cout << "Ваш выбор: ";

    if (!(std::cin >> choice))
    {
        std::cerr << "Ошибка: необходимо ввести число 1 или 2.\n";
        return 1;
    }

    switch (choice)
    {
    case 1:
    {
        // Заполняем матрицу случайными числами от 1 до 20.
        RandomGenerator randomGenerator(1, 20);
        randomGenerator.generate(matrix);
        break;
    }
    case 2:
    {
        // Заполняем матрицу значениями, введенными пользователем.
        ManualGenerator<int> manualGenerator;
        std::cout << "Введите элементы матрицы " << rows << "x" << cols << ":\n";

        if (!manualGenerator.generate(matrix, std::cin))
        {
            std::cerr << "Ошибка ввода элементов матрицы.\n";
            return 1;
        }
        break;
    }
    default:
        std::cerr << "Ошибка: выберите 1 или 2.\n";
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
    std::cout << "Результат Task2:\n" << task2.getMatrix() << "\n";

    return 0;
}
