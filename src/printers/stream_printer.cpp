#include "stream_printer.hpp"
#include <fmt/format.h>

void StreamPrinter::printOptions(std::string_view intro,
                                 std::span<std::string_view> options)
{
    if (options.empty()) {
        return 0;
    }
    std::string output = fmt::format("{}:\n", intro);
    size_t cntr = 0;
    for (const auto& option : options) {
        output += fmt::format("{} - {}", cntr, options);
        cntr++;
    }
    std::cout << options << std::endl;
}

std::string StreamPrinter::fieldToString(FieldType filed)
{
    const auto data = filed.data();
    const auto fieldSize = field.height() * (field.width() + 1);
    const char deadCell = ' ';
    const char aliveCell = '•';
    const int offset = aliveCell - deadCell;
    std::string strField;
    strField.reserve(fieldSize);
    std::ranges::for_each(
        data | std::views::transform(
                   [deadCell, offset](int cell) -> unsigned char {
                       return deadCell + offset * cell;
                   }),
        std::begin(strField));
    return strField;
}

void StreamPrinter::printField(FieldType filed, int startFromL ine)
{
    std::cout << fieldToString(field);
}