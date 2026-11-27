#include "RandomGenerator.h"
#include <stdexcept>

namespace {
/// Проверяет границы диапазона; бросает std::invalid_argument при minValue > maxValue.
int CheckedMin(int minValue, int maxValue) {
    if (minValue > maxValue) throw std::invalid_argument("Нижняя граница больше верхней");
    return minValue;
}
}  // namespace

RandomGenerator::RandomGenerator(int minValue, int maxValue)
    : engine_(std::random_device{}()), distribution_(CheckedMin(minValue, maxValue), maxValue) {}

void RandomGenerator::Fill(Matrix& matrix) {
    for (std::size_t r = 0; r < matrix.GetRows(); ++r)
        for (std::size_t c = 0; c < matrix.GetCols(); ++c) matrix.Set(r, c, distribution_(engine_));
}
