#ifndef FIELD_HPP
#define FIELD_HPP
#include <ranges>
#include <span>
#include <vector>

namespace life {
class Field {
    using CellType = uint8_t;
    size_t d_width;
    size_t d_height;
    std::vector<CellType> d_dataBlob;
    std::span<CellType> d_data;

  public:
    Field(size_t width, size_t height)
        : d_width(width), d_height(height),
          d_dataBlob((width + 2) * (height + 2)),
          d_data(std::next(d_dataBlob.begin(), 1 + width), width * height)
    {
    }

    Field(size_t width, size_t height, std::span<const uint8_t> data)
        : d_width(width), d_height(height),
          d_dataBlob((width + 2) * (height + 2)),
          d_data(std::next(d_dataBlob.begin(), 1 + width), width * height)
    {
        std::ranges::copy(data, std::next(d_dataBlob.begin(), 1 + width));
    }

    inline auto width() const { return d_width; }

    inline auto height() const { return d_height; }

    inline auto data() const { return d_data; }

    inline CellType& at(int y, int x) const { return d_data[y * d_width + x]; }
};
} // namespace life

#endif