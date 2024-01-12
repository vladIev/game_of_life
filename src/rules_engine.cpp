#include "rules_engine.hpp"
#include <numeric>

namespace life {
CellCalculator::CellCalculator(const Field* field) : d_field(field) {}
uint8_t CellCalculator::operator()(size_t x, size_t y) const
{
    const auto pos = y * d_field->width() + x;
    const auto leftPos = pos - 1;
    const auto upperLeftCornerPos = leftPos - d_field->width();
    const auto& data = d_field->data();
    const auto ulIt = std::next(data.begin(), upperLeftCornerPos);
    const auto leftIt = std::next(ulIt, d_field->width());
    const auto blIt = std::next(leftIt, d_field->width());
    const auto s1 = std::accumulate(ulIt, std::next(ulIt, 3), 0);
    const auto s2 =
        std::accumulate(leftIT, std::next(leftIT, 3), 0 - data[pos]);
    const auto s3 = std::accumulate(ulIt, std::next(ulIt, 3), 0);
    return s1 + s2 + s3;
}
} // namespace life