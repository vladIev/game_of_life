#include "stream_printer.hpp"

#include <iterator>
#include <ranges>

namespace life {

void StreamPrinter::printOptions(std::string_view intro,
                                 std::span<const std::string_view> options)
{
    if (options.empty()) {
        return;
    }
    (*d_stream) << intro << ":\n";
    size_t cntr = 1;
    for (const auto& option : options) {
        (*d_stream) << cntr << " - " << option << "\n";
        cntr++;
    }
}
std::string StreamPrinter::fieldToString(FieldType field) const
{
    const auto data = field.data();
    const auto fieldSize = field.height() * (field.width() + 1);
    const char deadCell = ' ';
    const char aliveCell = 'o';
    const int offset = aliveCell - deadCell;
    std::string strField;
    strField.reserve(fieldSize);
    std::ranges::copy(std::views::transform(
                          data,
                          [deadCell, offset](uint8_t cell) -> unsigned char {
                              return deadCell + offset * cell;
                          }),
                      std::back_inserter(strField));
    return strField;
}

void StreamPrinter::printField(const FieldType& field)
{
    const auto str = fieldToString(field);
    for (const auto i : std::views::iota(0, field.height())) {
        (*d_stream) << std::string_view(&str[i * field.width()], field.width())
                    << "\n";
    }
}
} // namespace life
