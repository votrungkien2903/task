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

    // Создаем матрицу и заполняем ее значениями, введенными пользователем.
    Matrix<int> matrix(rows, cols);
    ManualGenerator<int> manualGenerator;

    std::cout << "Введите элементы матрицы " << rows << "x" << cols << ":\n";
    if (!manualGenerator.generate(matrix, std::cin))
    {
        std::cerr << "Ошибка ввода элементов матрицы.\n";
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
    std::cout << "Результат Task2:\n" << task2.getMatrix() << "\n\n";

    // Дополнительно демонстрируем заполнение случайными числами.
    Matrix<int> randomMatrix(rows, cols);
    RandomGenerator randomGenerator(1, 20);
    randomGenerator.generate(randomMatrix);
    std::cout << "Матрица со случайными числами:\n" << randomMatrix << '\n';

    return 0;
}
