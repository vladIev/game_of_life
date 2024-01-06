#ifndef STREAM_PRINTER_HPP
#define STREAM_PRINTER_HPP
#include <iostream>
#include <span>
#include <string>

namespace life {
struct FieldType {
    std::array<uint8_t, 80 * 24> d_data;
    int width() const { return 80; }

    int height() const { return 24; }

    auto data() const { return std::span(d_data.begin(), d_data.end()); }
};
class StreamPrinter {
    std::ostream* d_stream;
    std::string fieldToString(FieldType field) const;

  public:
    StreamPrinter(std::ostream* stream) : d_stream(stream) {}
    void printOptions(std::string_view intro,
                      std::span<const std::string_view> options);
    void printField(const FieldType& filed);
};

} // namespace life
#endif