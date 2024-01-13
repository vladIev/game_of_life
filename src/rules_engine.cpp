#include "rules_engine.hpp"
#include <numeric>

namespace life {
CellCalculator::CellCalculator(const Field* field) : d_field(field) {}
uint8_t CellCalculator::operator()(size_t x, size_t y) const
{
    uint8_t sum1 = 0, sum2 = 0, sum3 = 0;
    for (int i = 0, pos = x - 1; i < 3; ++i, ++pos) {
        sum1 += d_field->at(pos, y - 1);
        sum2 += d_field->at(pos, y);
        sum3 += d_field->at(pos, y + 1);
    }
    const auto sum = sum1 + sum2 + sum3;
    return static_cast<uint8_t>(sum == 2 || sum == 3);
}
} // namespace life