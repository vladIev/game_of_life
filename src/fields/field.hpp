#ifndef FIELD_HPP
#define FIELD_HPP
#include <cassert>
#include <cstdint>
#include <ranges>
#include <span>
#include <vector>

namespace life {
class Field {
    using CellType = uint8_t;
    size_t d_width;
    size_t d_height;
    std::vector<std::vector<CellType>> d_dataBlob;
    std::vector<std::span<CellType>> d_data;

  public:
    Field(size_t width, size_t height) : d_width(width), d_height(height)
    {
        d_dataBlob.resize(d_height + 2);
        for (auto& row : d_dataBlob) {
            row.resize(d_width + 2);
        }

        d_data.reserve(d_height);
        for (auto& row : d_dataBlob) {
            d_data.emplace_back(std::next(row.begin(), 1), d_width);
        }
    }

    Field(size_t width,
          size_t height,
          std::span<std::span<const CellType>> data)
        : Field(width, height)

    {
        assert(d_height == data.size());

        auto dst = d_data.begin();
        for (const auto& row : data) {
            assert(d_width == row.size());
            std::ranges::copy(row.begin(), row.end(), dst);
            ++dst;
        }
    }

    [[nodiscard]] inline auto width() const { return d_width; }

    [[nodiscard]] inline auto height() const { return d_height; }

    [[nodiscard]] inline auto data() const { return d_data; }

    [[nodiscard]] inline CellType& at(int y, int x) const
    {
        return d_data[y][x];
    }
};
} // namespace life

#endif