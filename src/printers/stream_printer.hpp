#ifndef STREAM_PRINTER_HPP
#define STREAM_PRINTER_HPP
#include "fields/filed.hpp"

#include <ostream>
#include <span>
#include <string>

namespace life {

class StreamPrinter {
    std::ostream* d_stream;
    std::string fieldToString(Field field) const;

  public:
    StreamPrinter(std::ostream* stream) : d_stream(stream) {}
    void printOptions(std::string_view intro,
                      std::span<const std::string_view> options);
    void printField(const Field& filed);
};

} // namespace life
#endif