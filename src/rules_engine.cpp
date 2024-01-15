#include "rules_engine.hpp"
#include <numeric>

namespace life {
CellCalculator::CellCalculator(const Field* field) : d_field(field) {}
uint8_t CellCalculator::operator()(size_t x, size_t y) const
{
    uint8_t sum1 = 0, sum2 = 0, sum3 = 0;

    for (int pos = std::max(static_cast<int>(x - 1), 0);
         pos <= std::min(x + 1, d_field->width() - 1);
         ++pos) {
        if (y > 0)
            sum1 += d_field->at(pos, y - 1);
        sum2 += d_field->at(pos, y);
        if (y < d_field->height())
            sum3 += d_field->at(pos, y + 1);
    }
    const auto sum = sum1 + sum2 + sum3;
    return static_cast<uint8_t>(sum == 3);
}
} // namespace life