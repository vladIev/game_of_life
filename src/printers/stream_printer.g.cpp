#include "stream_printer.hpp"
#include <ranges>
#include <sstream>

#include <gtest/gtest.h>

using namespace life;
std::pair<FieldType, std::string> getDummyField()
{
    constexpr std::array<unsigned char, 2> cells{' ', 'o'};
    FieldType field;
    std::stringstream expected;
    for (auto i : std::views::iota(0, field.height())) {
        for (auto j : std::views::iota(0, field.width())) {
            uint8_t val = (i + j) % 2;
            field.d_data[i * field.width() + j] = val;
            expected << cells[val];
        }
        expected << "\n";
    }
    return std::make_pair(field, expected.str());
}

TEST(stream_printer, print_dummy)
{
    const auto [field, expected] = getDummyField();
    std::stringstream str;
    StreamPrinter printer(&str);
    printer.printField(field);

    EXPECT_EQ(str.str(), expected);
}

TEST(stream_printer, print_options)
{
    const std::vector<std::string_view> options{
        "option1", "option2", "option3"};
    const std::string expected =
        "Test options:\n1 - option1\n2 - option2\n3 - option3\n";

    std::stringstream str;
    StreamPrinter printer(&str);
    printer.printOptions("Test options", options);

    EXPECT_EQ(str.str(), expected);
}