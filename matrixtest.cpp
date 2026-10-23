
#include "CppUnitTest.h"

#include "../solution/Matrix.h"
#include "../solution/task1.h"
#include "../solution/task2.h"
#include "../solution/RandomGenerator.h"
#include "../solution/constant.h"
#include "../solution/zerogenerator.h"

#include <sstream>
#include <string>
#include <utility>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTests
{
    TEST_CLASS(MatrixTests)
    {
    public:

        // Проверяет конструктор матрицы и доступ к ее элементам.
        TEST_METHOD(MatrixConstructorTest)
        {
            Matrix<int> matrix(2, 3);

            Assert::AreEqual(static_cast<size_t>(2), matrix.getRows());
            Assert::AreEqual(static_cast<size_t>(3), matrix.getCols());

            matrix[0][0] = 1;
            matrix[0][1] = 2;
            matrix[0][2] = 3;
            matrix[1][0] = 4;
            matrix[1][1] = 5;
            matrix[1][2] = 6;

            Assert::AreEqual(1, matrix[0][0]);
            Assert::AreEqual(6, matrix[1][2]);
        }

        // Проверяет конструктор матрицы без параметров.
        TEST_METHOD(MatrixDefaultConstructorTest)
        {
            Matrix<int> matrix;

            Assert::AreEqual(static_cast<size_t>(0), matrix.getRows());
            Assert::AreEqual(static_cast<size_t>(0), matrix.getCols());
        }

        // Проверяет матрицу с нулевым количеством строк.
        TEST_METHOD(MatrixZeroRowsTest)
        {
            Matrix<int> matrix(0, 3);

            Assert::AreEqual(static_cast<size_t>(0), matrix.getRows());
            Assert::AreEqual(static_cast<size_t>(3), matrix.getCols());
        }

        // Проверяет матрицу с нулевым количеством столбцов.
        TEST_METHOD(MatrixZeroColsTest)
        {
            Matrix<int> matrix(3, 0);

            Assert::AreEqual(static_cast<size_t>(3), matrix.getRows());
            Assert::AreEqual(static_cast<size_t>(0), matrix.getCols());
        }

        // Проверяет конструктор копирования.
        TEST_METHOD(MatrixCopyConstructorTest)
        {
            Matrix<int> original(2, 2);
            original[0][0] = 1;
            original[0][1] = 2;
            original[1][0] = 3;
            original[1][1] = 4;

            Matrix<int> copy(original);

            Assert::AreEqual(static_cast<size_t>(2), copy.getRows());
            Assert::AreEqual(static_cast<size_t>(2), copy.getCols());
            Assert::AreEqual(1, copy[0][0]);
            Assert::AreEqual(4, copy[1][1]);

            // Изменение копии не должно менять оригинал.
            copy[0][0] = 100;
            Assert::AreEqual(1, original[0][0]);
        }

        // Проверяет конструктор перемещения.
        TEST_METHOD(MatrixMoveConstructorTest)
        {
            Matrix<int> original(2, 2);
            original[0][0] = 10;
            original[1][1] = 20;

            Matrix<int> moved(std::move(original));

            Assert::AreEqual(static_cast<size_t>(2), moved.getRows());
            Assert::AreEqual(static_cast<size_t>(2), moved.getCols());
            Assert::AreEqual(10, moved[0][0]);
            Assert::AreEqual(20, moved[1][1]);

            Assert::AreEqual(static_cast<size_t>(0), original.getRows());
            Assert::AreEqual(static_cast<size_t>(0), original.getCols());
        }

        // Проверяет оператор присваивания копированием.
        TEST_METHOD(MatrixCopyAssignmentTest)
        {
            Matrix<int> original(2, 2);
            original[0][0] = 1;
            original[1][1] = 9;

            Matrix<int> target(1, 1);
            target = original;

            Assert::AreEqual(static_cast<size_t>(2), target.getRows());
            Assert::AreEqual(static_cast<size_t>(2), target.getCols());
            Assert::AreEqual(1, target[0][0]);
            Assert::AreEqual(9, target[1][1]);

            target[0][0] = 50;
            Assert::AreEqual(1, original[0][0]);
        }

        // Проверяет оператор присваивания перемещением.
        TEST_METHOD(MatrixMoveAssignmentTest)
        {
            Matrix<int> original(2, 2);
            original[0][0] = 7;
            original[1][1] = 8;

            Matrix<int> target(1, 1);
            target = std::move(original);

            Assert::AreEqual(static_cast<size_t>(2), target.getRows());
            Assert::AreEqual(static_cast<size_t>(2), target.getCols());
            Assert::AreEqual(7, target[0][0]);
            Assert::AreEqual(8, target[1][1]);

            Assert::AreEqual(static_cast<size_t>(0), original.getRows());
            Assert::AreEqual(static_cast<size_t>(0), original.getCols());
        }

        // Проверяет доступ к элементам через неконстантную матрицу.
        TEST_METHOD(MatrixNonConstAccessTest)
        {
            Matrix<int> matrix(1, 2);
            matrix[0][0] = 15;
            matrix[0][1] = 25;

            Assert::AreEqual(15, matrix[0][0]);
            Assert::AreEqual(25, matrix[0][1]);
        }

        // Проверяет доступ к элементам через константную матрицу.
        TEST_METHOD(MatrixConstAccessTest)
        {
            Matrix<int> matrix(1, 2);
            matrix[0][0] = 15;
            matrix[0][1] = 25;

            const Matrix<int>& constMatrix = matrix;

            Assert::AreEqual(15, constMatrix[0][0]);
            Assert::AreEqual(25, constMatrix[0][1]);
        }

        // Проверяет обработку выхода индекса строки за границы.
        TEST_METHOD(MatrixOutOfRangeTest)
        {
            Matrix<int> matrix(2, 2);

            Assert::ExpectException<std::out_of_range>(
                [&matrix]()
                {
                    matrix[2];
                }
            );
        }

        // Проверяет преобразование матрицы в строку.
        TEST_METHOD(MatrixToStringTest)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 1;
            matrix[0][1] = 2;
            matrix[1][0] = 3;
            matrix[1][1] = 4;

            std::string result = matrix.toString();

            Assert::IsTrue(!result.empty());
            Assert::IsTrue(result.find("1") != std::string::npos);
            Assert::IsTrue(result.find("4") != std::string::npos);
        }

        // Проверяет оператор вывода матрицы в поток.
        TEST_METHOD(MatrixOutputOperatorTest)
        {
            Matrix<int> matrix(1, 2);
            matrix[0][0] = 11;
            matrix[0][1] = 22;

            std::ostringstream output;
            output << matrix;

            Assert::IsTrue(!output.str().empty());
            Assert::IsTrue(output.str().find("11") != std::string::npos);
            Assert::IsTrue(output.str().find("22") != std::string::npos);
        }

        // Проверяет оператор ввода матрицы из потока.
        TEST_METHOD(MatrixInputOperatorTest)
        {
            Matrix<int> matrix(2, 2);
            std::istringstream input("1 2 3 4");

            input >> matrix;

            Assert::AreEqual(1, matrix[0][0]);
            Assert::AreEqual(2, matrix[0][1]);
            Assert::AreEqual(3, matrix[1][0]);
            Assert::AreEqual(4, matrix[1][1]);
        }

        // Проверяет замену максимального элемента каждой строки нулем.
        TEST_METHOD(Task1Test)
        {
            Matrix<int> matrix(3, 3);

            matrix[0][0] = 1;
            matrix[0][1] = 5;
            matrix[0][2] = 3;

            matrix[1][0] = 7;
            matrix[1][1] = 2;
            matrix[1][2] = 4;

            matrix[2][0] = 9;
            matrix[2][1] = 6;
            matrix[2][2] = 8;

            RandomGenerator generator(1, 10);
            Task1<int> task(matrix, &generator);

            task.solve();

            Assert::AreEqual(0, task.getMatrix()[0][1]);
            Assert::AreEqual(0, task.getMatrix()[1][0]);
            Assert::AreEqual(0, task.getMatrix()[2][0]);

            Assert::AreEqual(1, task.getMatrix()[0][0]);
            Assert::AreEqual(2, task.getMatrix()[1][1]);
        }

        // Проверяет Task1 для пустой матрицы.
        TEST_METHOD(Task1EmptyMatrixTest)
        {
            Matrix<int> matrix;
            RandomGenerator generator(1, 10);
            Task1<int> task(matrix, &generator);

            task.solve();

            Assert::AreEqual(
                static_cast<size_t>(0),
                task.getMatrix().getRows()
            );
            Assert::AreEqual(
                static_cast<size_t>(0),
                task.getMatrix().getCols()
            );
        }

        // Проверяет, что Task1 не изменяет элементы, не являющиеся максимумами.
        TEST_METHOD(Task1PreservesOtherElementsTest)
        {
            Matrix<int> matrix(1, 3);
            matrix[0][0] = 2;
            matrix[0][1] = 8;
            matrix[0][2] = 4;

            RandomGenerator generator(1, 10);
            Task1<int> task(matrix, &generator);

            task.solve();

            Assert::AreEqual(2, task.getMatrix()[0][0]);
            Assert::AreEqual(0, task.getMatrix()[0][1]);
            Assert::AreEqual(4, task.getMatrix()[0][2]);
        }

        // Проверяет вставку нулевых строк перед подходящими строками.
        TEST_METHOD(Task2Test)
        {
            Matrix<int> matrix(4, 3);

            matrix[0][0] = 3;
            matrix[0][1] = 4;
            matrix[0][2] = 5;

            matrix[1][0] = 2;
            matrix[1][1] = 6;
            matrix[1][2] = 7;

            matrix[2][0] = 6;
            matrix[2][1] = 8;
            matrix[2][2] = 9;

            matrix[3][0] = 9;
            matrix[3][1] = 1;
            matrix[3][2] = 2;

            RandomGenerator generator(1, 10);
            Task2<int> task(matrix, &generator);

            task.solve();

            Assert::AreEqual(
                static_cast<size_t>(7),
                task.getMatrix().getRows()
            );
            Assert::AreEqual(
                static_cast<size_t>(3),
                task.getMatrix().getCols()
            );

            // Нулевая строка перед первой исходной строкой.
            Assert::AreEqual(0, task.getMatrix()[0][0]);
            Assert::AreEqual(0, task.getMatrix()[0][1]);
            Assert::AreEqual(0, task.getMatrix()[0][2]);

            // Первая исходная строка.
            Assert::AreEqual(3, task.getMatrix()[1][0]);
            Assert::AreEqual(4, task.getMatrix()[1][1]);

            // Вторая исходная строка не требует вставки.
            Assert::AreEqual(2, task.getMatrix()[2][0]);

            // Нулевая строка перед третьей исходной строкой.
            Assert::AreEqual(0, task.getMatrix()[3][0]);

            // Третья исходная строка.
            Assert::AreEqual(6, task.getMatrix()[4][0]);

            // Нулевая строка перед четвертой исходной строкой.
            Assert::AreEqual(0, task.getMatrix()[5][0]);

            // Четвертая исходная строка.
            Assert::AreEqual(9, task.getMatrix()[6][0]);
        }

        // Проверяет Task2, если ни один первый элемент не делится на 3.
        TEST_METHOD(Task2NoInsertionTest)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 1;
            matrix[0][1] = 5;
            matrix[1][0] = 2;
            matrix[1][1] = 6;

            RandomGenerator generator(1, 10);
            Task2<int> task(matrix, &generator);

            task.solve();

            Assert::AreEqual(
                static_cast<size_t>(2),
                task.getMatrix().getRows()
            );
            Assert::AreEqual(1, task.getMatrix()[0][0]);
            Assert::AreEqual(5, task.getMatrix()[0][1]);
            Assert::AreEqual(2, task.getMatrix()[1][0]);
            Assert::AreEqual(6, task.getMatrix()[1][1]);
        }

        // Проверяет Task2 для пустой матрицы.
        TEST_METHOD(Task2EmptyMatrixTest)
        {
            Matrix<int> matrix;
            RandomGenerator generator(1, 10);
            Task2<int> task(matrix, &generator);

            task.solve();

            Assert::AreEqual(
                static_cast<size_t>(0),
                task.getMatrix().getRows()
            );
            Assert::AreEqual(
                static_cast<size_t>(0),
                task.getMatrix().getCols()
            );
        }

        // Проверяет генератор случайных целых чисел.
        TEST_METHOD(RandomGeneratorTest)
        {
            Matrix<int> matrix(10, 10);
            RandomGenerator generator(1, 10);

            generator.generate(matrix);

            for (size_t i = 0; i < matrix.getRows(); ++i)
            {
                for (size_t j = 0; j < matrix.getCols(); ++j)
                {
                    Assert::IsTrue(matrix[i][j] >= 1);
                    Assert::IsTrue(matrix[i][j] <= 10);
                }
            }
        }

        // Проверяет генератор постоянного значения.
        TEST_METHOD(ConstantGeneratorTest)
        {
            Matrix<int> matrix(2, 3);
            Constant<int> generator(7);

            generator.generate(matrix);

            for (size_t i = 0; i < matrix.getRows(); ++i)
            {
                for (size_t j = 0; j < matrix.getCols(); ++j)
                {
                    Assert::AreEqual(7, matrix[i][j]);
                }
            }
        }

        // Проверяет генератор нулевых значений.
        TEST_METHOD(ZeroGeneratorTest)
        {
            Matrix<int> matrix(2, 3);

            for (size_t i = 0; i < matrix.getRows(); ++i)
            {
                for (size_t j = 0; j < matrix.getCols(); ++j)
                {
                    matrix[i][j] = 99;
                }
            }

            ZeroGenerator<int> generator;
            generator.generate(matrix);

            for (size_t i = 0; i < matrix.getRows(); ++i)
            {
                for (size_t j = 0; j < matrix.getCols(); ++j)
                {
                    Assert::AreEqual(0, matrix[i][j]);
                }
            }
        }
    };
}
