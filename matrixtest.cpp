#include "CppUnitTest.h"

#include "../solution/Matrix.h"
#include "../solution/task1.h"
#include "../solution/task2.h"
#include "../solution/RandomGenerator.h"

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

            matrix[0][0] = 1;
            matrix[0][1] = 2;
            matrix[0][2] = 3;

            matrix[1][0] = 4;
            matrix[1][1] = 5;
            matrix[1][2] = 6;

            Assert::AreEqual((size_t)2, matrix.getRows());
            Assert::AreEqual((size_t)3, matrix.getCols());

            Assert::AreEqual(1, matrix[0][0]);
            Assert::AreEqual(6, matrix[1][2]);
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


        // Проверяет вставку нулевых строк перед строками,
        // первый элемент которых делится на 3.
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

            Assert::AreEqual((size_t)7, task.getMatrix().getRows());

            // Нулевая строка перед первой строкой.
            Assert::AreEqual(0, task.getMatrix()[0][0]);
            Assert::AreEqual(0, task.getMatrix()[0][1]);
            Assert::AreEqual(0, task.getMatrix()[0][2]);

            // Исходная первая строка.
            Assert::AreEqual(3, task.getMatrix()[1][0]);

            // Нулевая строка перед третьей исходной строкой.
            Assert::AreEqual(0, task.getMatrix()[3][0]);

            // Исходная третья строка.
            Assert::AreEqual(6, task.getMatrix()[4][0]);

            // Нулевая строка перед четвертой исходной строкой.
            Assert::AreEqual(0, task.getMatrix()[5][0]);

            // Исходная четвертая строка.
            Assert::AreEqual(9, task.getMatrix()[6][0]);
        }
    };
}