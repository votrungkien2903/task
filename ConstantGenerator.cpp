#include "ConstantGenerator.h"

ConstantGenerator::ConstantGenerator(const int value) : value_(value) {}

void ConstantGenerator::Fill(Matrix& matrix) {
    for (std::size_t r = 0; r < matrix.GetRows(); ++r)
        for (std::size_t c = 0; c < matrix.GetCols(); ++c) matrix.Set(r, c, value_);
}
