#include "CppUnitTest.h"

#include "matrix.h"
#include "Exercise.h"
#include "task1.h"
#include "task2.h"
#include "RandomGenerator.h"
#include "ManualGenerator.h"
#include "constant.h"

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
        // Проверяет создание матрицы заданного размера.
        TEST_METHOD(MatrixConstructorTest)
        {
            Matrix<int> matrix(2, 3);

            Assert::AreEqual(static_cast<std::size_t>(2), matrix.getRows());
            Assert::AreEqual(static_cast<std::size_t>(3), matrix.getCols());

            for (std::size_t i = 0; i < matrix.getRows(); ++i)
            {
                for (std::size_t j = 0; j < matrix.getCols(); ++j)
                {
                    Assert::AreEqual(0, matrix[i][j]);
                }
            }
        }

        // Проверяет создание пустой матрицы.
        TEST_METHOD(MatrixDefaultConstructorTest)
        {
            Matrix<int> matrix;
            Assert::AreEqual(static_cast<std::size_t>(0), matrix.getRows());
            Assert::AreEqual(static_cast<std::size_t>(0), matrix.getCols());
        }

        // Проверяет матрицу без строк.
        TEST_METHOD(MatrixZeroRowsTest)
        {
            Matrix<int> matrix(0, 3);
            Assert::AreEqual(static_cast<std::size_t>(0), matrix.getRows());
            Assert::AreEqual(static_cast<std::size_t>(3), matrix.getCols());
        }

        // Проверяет матрицу без столбцов.
        TEST_METHOD(MatrixZeroColsTest)
        {
            Matrix<int> matrix(3, 0);
            Assert::AreEqual(static_cast<std::size_t>(3), matrix.getRows());
            Assert::AreEqual(static_cast<std::size_t>(0), matrix.getCols());
        }

        // Проверяет конструктор копирования.
        TEST_METHOD(MatrixCopyConstructorTest)
        {
            Matrix<int> original(1, 2);
            original[0][0] = 4;
            original[0][1] = 8;

            Matrix<int> copy(original);
            Assert::AreEqual(4, copy[0][0]);
            Assert::AreEqual(8, copy[0][1]);

            copy[0][0] = 100;
            Assert::AreEqual(4, original[0][0]);
        }

        // Проверяет конструктор перемещения.
        TEST_METHOD(MatrixMoveConstructorTest)
        {
            Matrix<int> original(1, 1);
            original[0][0] = 12;

            Matrix<int> moved(std::move(original));
            Assert::AreEqual(12, moved[0][0]);
            Assert::AreEqual(static_cast<std::size_t>(0), original.getRows());
            Assert::AreEqual(static_cast<std::size_t>(0), original.getCols());
        }

        // Проверяет копирующее присваивание.
        TEST_METHOD(MatrixCopyAssignmentTest)
        {
            Matrix<int> original(1, 1);
            original[0][0] = 5;

            Matrix<int> target(2, 2);
            target = original;

            Assert::AreEqual(static_cast<std::size_t>(1), target.getRows());
            Assert::AreEqual(static_cast<std::size_t>(1), target.getCols());
            Assert::AreEqual(5, target[0][0]);
        }

        // Проверяет перемещающее присваивание.
        TEST_METHOD(MatrixMoveAssignmentTest)
        {
            Matrix<int> original(1, 1);
            original[0][0] = 9;

            Matrix<int> target;
            target = std::move(original);

            Assert::AreEqual(9, target[0][0]);
            Assert::AreEqual(static_cast<std::size_t>(0), original.getRows());
        }

        // Проверяет самоприсваивание копированием.
        TEST_METHOD(MatrixSelfAssignmentTest)
        {
            Matrix<int> matrix(1, 1);
            matrix[0][0] = 7;
            matrix = matrix;
            Assert::AreEqual(7, matrix[0][0]);
        }

        // Проверяет доступ к строкам и элементам.
        TEST_METHOD(MatrixElementAccessTest)
        {
            Matrix<int> matrix(1, 2);
            matrix[0][0] = 3;
            matrix[0][1] = 6;

            const Matrix<int>& constMatrix = matrix;
            Assert::AreEqual(3, constMatrix[0][0]);
            Assert::AreEqual(6, constMatrix[0][1]);
        }

        // Проверяет исключение при выходе индекса за границы.
        TEST_METHOD(MatrixOutOfRangeTest)
        {
            Matrix<int> matrix(1, 1);
            Assert::ExpectException<std::out_of_range>([&matrix]() { matrix[1]; });
        }

        // Проверяет строковое представление матрицы.
        TEST_METHOD(MatrixToStringTest)
        {
            Matrix<int> matrix(2, 2);
            matrix[0][0] = 1;
            matrix[0][1] = 2;
            matrix[1][0] = 3;
            matrix[1][1] = 4;

            Assert::AreEqual(std::string("1 2\n3 4"), matrix.toString());
        }

        // Проверяет вывод матрицы в поток.
        TEST_METHOD(MatrixOutputOperatorTest)
        {
            Matrix<int> matrix(1, 2);
            matrix[0][0] = 10;
            matrix[0][1] = 20;

            std::ostringstream output;
            output << matrix;
            Assert::AreEqual(std::string("10 20"), output.str());
        }

        // Проверяет ввод элементов матрицы из потока.
        TEST_METHOD(MatrixInputOperatorTest)
        {
            Matrix<int> matrix(2, 2);
            std::istringstream input("1 2 3 4");

            input >> matrix;

            Assert::IsTrue(static_cast<bool>(input));
            Assert::AreEqual(1, matrix[0][0]);
            Assert::AreEqual(4, matrix[1][1]);
        }

        // Проверяет обработку недостаточного количества входных данных.
        TEST_METHOD(MatrixInputFailureTest)
        {
            Matrix<int> matrix(1, 2);
            std::istringstream input("5");

            input >> matrix;
            Assert::IsTrue(input.fail());
            Assert::AreEqual(5, matrix[0][0]);
        }

        // Проверяет заполнение матрицы генератором.
        TEST_METHOD(MatrixFillTest)
        {
            Matrix<int> matrix(2, 2);
            Constant<int> generator(6);

            matrix.fill(generator);

            for (std::size_t i = 0; i < matrix.getRows(); ++i)
            {
                for (std::size_t j = 0; j < matrix.getCols(); ++j)
                {
                    Assert::AreEqual(6, matrix[i][j]);
                }
            }
        }

        // Проверяет получение матрицы из базового класса Exercise.
        TEST_METHOD(ExerciseGetMatrixTest)
        {
            Matrix<int> matrix(1, 1);
            matrix[0][0] = 14;

            Task1<int> task(matrix);
            Assert::AreEqual(14, task.getMatrix()[0][0]);
        }

        // Проверяет замену максимального элемента каждой строки нулем.
        TEST_METHOD(Task1Test)
        {
            Matrix<int> matrix(2, 3);
            matrix[0][0] = 1; matrix[0][1] = 5; matrix[0][2] = 3;
            matrix[1][0] = 7; matrix[1][1] = 2; matrix[1][2] = 4;

            Task1<int> task(matrix);
            task.solve();

            Assert::AreEqual(0, task.getMatrix()[0][1]);
            Assert::AreEqual(0, task.getMatrix()[1][0]);
            Assert::AreEqual(1, task.getMatrix()[0][0]);
            Assert::AreEqual(2, task.getMatrix()[1][1]);
        }

        // Проверяет Task1 для пустой матрицы.
        TEST_METHOD(Task1EmptyMatrixTest)
        {
            Matrix<int> matrix;
            Task1<int> task(matrix);
            task.solve();

            Assert::AreEqual(static_cast<std::size_t>(0), task.getMatrix().getRows());
            Assert::AreEqual(static_cast<std::size_t>(0), task.getMatrix().getCols());
        }

        // Проверяет Task1 при нескольких одинаковых максимумах.
        TEST_METHOD(Task1EqualMaximumsTest)
        {
            Matrix<int> matrix(1, 3);
            matrix[0][0] = 8;
            matrix[0][1] = 8;
            matrix[0][2] = 2;

            Task1<int> task(matrix);
            task.solve();

            Assert::AreEqual(0, task.getMatrix()[0][0]);
            Assert::AreEqual(8, task.getMatrix()[0][1]);
            Assert::AreEqual(2, task.getMatrix()[0][2]);
        }

        // Проверяет, что Task1 не изменяет исходную матрицу.
        TEST_METHOD(Task1PreservesSourceMatrixTest)
        {
            Matrix<int> matrix(1, 2);
            matrix[0][0] = 2;
            matrix[0][1] = 9;

            Task1<int> task(matrix);
            task.solve();

            Assert::AreEqual(9, matrix[0][1]);
            Assert::AreEqual(0, task.getMatrix()[0][1]);
        }

        // Проверяет вставку нулевых строк перед подходящими строками.
        TEST_METHOD(Task2Test)
        {
            Matrix<int> matrix(4, 2);
            matrix[0][0] = 3; matrix[0][1] = 4;
            matrix[1][0] = 2; matrix[1][1] = 5;
            matrix[2][0] = 6; matrix[2][1] = 7;
            matrix[3][0] = 9; matrix[3][1] = 8;

            Task2<int> task(matrix);
            task.solve();

            const Matrix<int>& result = task.getMatrix();
            Assert::AreEqual(static_cast<std::size_t>(7), result.getRows());
            Assert::AreEqual(static_cast<std::size_t>(2), result.getCols());

            Assert::AreEqual(0, result[0][0]);
            Assert::AreEqual(3, result[1][0]);
            Assert::AreEqual(2, result[2][0]);
            Assert::AreEqual(0, result[3][0]);
            Assert::AreEqual(6, result[4][0]);
            Assert::AreEqual(0, result[5][0]);
            Assert::AreEqual(9, result[6][0]);
        }

        // Проверяет Task2, если вставка не требуется.
        TEST_METHOD(Task2NoInsertionTest)
        {
            Matrix<int> matrix(2, 1);
            matrix[0][0] = 1;
            matrix[1][0] = 2;

            Task2<int> task(matrix);
            task.solve();

            Assert::AreEqual(static_cast<std::size_t>(2), task.getMatrix().getRows());
            Assert::AreEqual(1, task.getMatrix()[0][0]);
            Assert::AreEqual(2, task.getMatrix()[1][0]);
        }

        // Проверяет Task2 для пустой матрицы.
        TEST_METHOD(Task2EmptyMatrixTest)
        {
            Matrix<int> matrix;
            Task2<int> task(matrix);
            task.solve();
            Assert::AreEqual(static_cast<std::size_t>(0), task.getMatrix().getRows());
        }

        // Проверяет Task2 для матрицы без столбцов.
        TEST_METHOD(Task2ZeroColsTest)
        {
            Matrix<int> matrix(3, 0);
            Task2<int> task(matrix);
            task.solve();
            Assert::AreEqual(static_cast<std::size_t>(3), task.getMatrix().getRows());
            Assert::AreEqual(static_cast<std::size_t>(0), task.getMatrix().getCols());
        }

        // Проверяет генерацию случайных чисел в заданном диапазоне.
        TEST_METHOD(RandomGeneratorTest)
        {
            Matrix<int> matrix(10, 10);
            RandomGenerator generator(1, 10);
            matrix.fill(generator);

            for (std::size_t i = 0; i < matrix.getRows(); ++i)
            {
                for (std::size_t j = 0; j < matrix.getCols(); ++j)
                {
                    Assert::IsTrue(matrix[i][j] >= 1 && matrix[i][j] <= 10);
                }
            }
        }

        // Проверяет, что RandomGenerator отклоняет некорректный диапазон.
        TEST_METHOD(RandomGeneratorInvalidRangeTest)
        {
            Assert::ExpectException<std::invalid_argument>(
                []() { RandomGenerator generator(10, 1); }
            );
        }

        // Проверяет ручное заполнение матрицы.
        TEST_METHOD(ManualGeneratorTest)
        {
            Matrix<int> matrix(2, 2);
            std::istringstream input("1 2 3 4");
            ManualGenerator<int> generator(input);

            matrix.fill(generator);

            Assert::AreEqual(1, matrix[0][0]);
            Assert::AreEqual(4, matrix[1][1]);
        }

        // Проверяет сохранение матрицы при ошибке ручного ввода.
        TEST_METHOD(ManualGeneratorInputFailureTest)
        {
            Matrix<int> matrix(1, 2);
            matrix[0][0] = 7;
            matrix[0][1] = 8;

            std::istringstream input("1");
            ManualGenerator<int> generator(input);

            Assert::ExpectException<std::runtime_error>(
                [&matrix, &generator]() { matrix.fill(generator); }
            );

            Assert::AreEqual(7, matrix[0][0]);
            Assert::AreEqual(8, matrix[0][1]);
        }

        // Проверяет возврат постоянного значения генератором.
        TEST_METHOD(ConstantGeneratorTest)
        {
            Constant<int> generator(7);
            Assert::AreEqual(7, generator.generate());
        }
    };
}
