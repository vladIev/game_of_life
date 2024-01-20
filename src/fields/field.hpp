#ifndef FIELD_HPP
#define FIELD_HPP
#include <algorithm>
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
    std::vector<CellType> d_dataBlob;

  public:
    Field(size_t width, size_t height) : d_width(width), d_height(height)
    {
        d_dataBlob.resize(d_height * d_width);
    }

    Field(size_t width, size_t height, std::span<const CellType> data)
        : Field(width, height)

    {
        assert(d_height * d_width == data.size());
        std::ranges::copy(data.begin(), data.end(), d_dataBlob.data());
    }

    [[nodiscard]] inline auto width() const { return d_width; }

    [[nodiscard]] inline auto height() const { return d_height; }

    [[nodiscard]] inline auto data() const { return std::span(d_dataBlob); }

    [[nodiscard]] inline CellType& at(int y, int x)
    {
        assert(y >= 0 && y < d_height);
        assert(x >= 0 && x < d_width);
        return d_dataBlob[y * d_width + x];
    }

    [[nodiscard]] inline const CellType& at(int y, int x) const
    {
        assert(y >= 0 && y < d_height);
        assert(x >= 0 && x < d_width);
        return d_dataBlob[y * d_width + x];
    }
};
} // namespace life

#endif