#ifndef STREAM_PRINTER_HPP
#define STREAM_PRINTER_HPP
#include <iostream>
#include <span>
#include <string>

namespace life {
struct FieldType {
    std::array<std::array<uint8_t, 80>, 24> d_data;
    int width() const { return 80; }

    int height() const { return 24; }

    std::span<uint8_t> data() const
    {
        return std::span<uint8_t>(d_data.data(), widht() * height);
    }
};
class StreamPrinter {
    std::ostream d_stream;

  public:
    StreamPrinter(std::ostream stream) : d_stream(std::move(stream)) {}
    void printOptions(std::string_view intro,
                      std::span<std::string_view> options);
    void printField(FieldType filed);
};
} // namespace life
#endif