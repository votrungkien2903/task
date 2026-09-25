#include <iostream>

#include "matrix.h"
#include "randomgenerator.h"
#include "zerogenerator.h"
#include "constant.h"
#include "task1.h"
#include "task2.h"

int main()
{
    // Создаем матрицу 4x4.
    Matrix<int> matrix(4, 4);

    // Создаем генератор случайных чисел от 1 до 20.
    RandomGenerator randomGenerator(1, 20);

    // Заполняем матрицу случайными числами.
    randomGenerator.generate(matrix);

    // Выводим исходную матрицу.
    std::cout << "Исходная матрица:" << std::endl;
    std::cout << matrix << std::endl << std::endl;


    // Создаем объект первого задания.
    Task1<int> task1(matrix, &randomGenerator);

    // Выполняем первое задание.
    task1.solve();

    // Выводим результат первого задания.
    std::cout << "Результат Task1:" << std::endl;
    std::cout << task1.getMatrix() << std::endl << std::endl;


    // Создаем новую матрицу для второго задания.
    Matrix<int> matrix2(4, 4);

    // Заполняем матрицу случайными числами.
    randomGenerator.generate(matrix2);

    // Выводим исходную матрицу второго задания.
    std::cout << "Исходная матрица для Task2:" << std::endl;
    std::cout << matrix2 << std::endl << std::endl;


    // Создаем объект второго задания.
    Task2<int> task2(matrix2, &randomGenerator);

    // Выполняем второе задание.
    task2.solve();

    // Выводим результат второго задания.
    std::cout << "Результат Task2:" << std::endl;
    std::cout << task2.getMatrix() << std::endl << std::endl;


    return 0;
}