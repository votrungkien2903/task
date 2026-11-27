#include "KeyboardGenerator.h"
#include <stdexcept>
#include <utility>

KeyboardGenerator::KeyboardGenerator(ValueSupplier supplier) : supplier_(std::move(supplier)) {
    if (!supplier_) throw std::invalid_argument("Поставщик значений не задан");
}

void KeyboardGenerator::Fill(Matrix& matrix) {
    for (std::size_t r = 0; r < matrix.GetRows(); ++r)
        for (std::size_t c = 0; c < matrix.GetCols(); ++c) matrix.Set(r, c, supplier_(r, c));
}
