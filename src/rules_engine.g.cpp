#include "fields/filed.hpp"
#include "rules_engine.hpp"

#include <gtest/gtest.h>

#include <span>
#include <vector>

using namespace life;
TEST(cell_calculator, cell_dies)
{
    // clang-format off
    const std::vector<uint8_t> field {
        1,0,0,
        0,1,0,
        0,0,0
    };

    const std::vector<uint8_t> expected {
        0,0,0,
        0,0,0,
        0,0,0
    };

    // clang-format on

    Field f(3, 3, std::span<const uint8_t>(field));
    CellCalculator calculator(&f);

    std::vector<uint8_t> result;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            result.push_back(calculator(j, i));
        }
    }

    EXPECT_EQ(result, expected);
}