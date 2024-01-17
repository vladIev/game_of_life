#include "fields/field.hpp"
#include "rules_engine.hpp"

#include <gtest/gtest.h>

#include <span>
#include <vector>

using namespace life;
namespace {
auto nextGeneration(size_t width, size_t height, std::span<const uint8_t> field)
{
    Field f(width, height, field);
    CellCalculator calculator(&f);

    std::vector<uint8_t> result;
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            result.push_back(calculator(j, i));
        }
    }
    return result;
}
} // namespace

TEST(cell_calculator, cell_extincts)
{
    // clang-format off
    const std::vector<uint8_t> field {
        1,0,0,
        0,1,0,
        0,0,0
    };
    // clang-format on

    Field f(3, 3, field);
    CellCalculator calculator(&f);

    EXPECT_EQ(0, calculator(1, 1));
}

TEST(cell_calculator, cell_borns)
{
    // clang-format off
    const std::vector<uint8_t> field {
        1,1,0,
        0,0,0,
        0,0,1
    };

    const std::vector<uint8_t> expected {
        0,0,0,
        0,1,0,
        0,0,0
    };

    // clang-format on

    const auto result = nextGeneration(3, 3, field);
    EXPECT_EQ(result, expected);
}

TEST(cell_calculator, cell_stay_alive_with_2_neighbors)
{
    // clang-format off
    const std::vector<uint8_t> field {
        1,0,0,
        0,1,0,
        0,0,1
    };

    // clang-format on

    Field f(3, 3, field);
    CellCalculator calculator(&f);

    EXPECT_EQ(1, calculator(1, 1));
}

TEST(cell_calculator, cell_stay_alive_with_3_neighbors)
{
    // clang-format off
    const std::vector<uint8_t> field {
        1,0,1   ,
        0,1,0,
        0,0,1
    };
    // clang-format on

    Field f(3, 3, field);
    CellCalculator calculator(&f);

    EXPECT_EQ(1, calculator(1, 1));
}

TEST(cell_calculator, cell_dies_starvation)
{
    // clang-format off
    const std::vector<uint8_t> field {
        1,0,1,
        0,1,0,
        1,0,1
    };
    // clang-format on

    Field f(3, 3, field);
    CellCalculator calculator(&f);

    EXPECT_EQ(0, calculator(1, 1));
}

TEST(cell_calculator, borders_handling)
{
    // clang-format off
    const std::vector<uint8_t> field {
        1,0,1,
        0,1,1,
        1,0,1
    };
    // clang-format on

    Field f(3, 3, field);
    CellCalculator calculator(&f);

    EXPECT_EQ(0, calculator(0, 0));
    EXPECT_EQ(0, calculator(2, 0));
    EXPECT_EQ(1, calculator(0, 2));
    EXPECT_EQ(1, calculator(2, 2));
}

TEST(basic_rules_engine, get_next_generation)
{
    // clang-format off
    const std::vector<uint8_t> field {
        1,0,1,
        0,1,1,
        1,0,1
    };

    const std::vector<uint8_t> expected {
        0,0,1,
        1,0,1,
        0,0,1
    };
    // clang-format on

    Field f(3, 3, field);
    BasicRulesEngine engine;
    auto next = engine.getNextGeneration(f);
    EXPECT_TRUE(std::ranges::equal(next.data(), expected));
}
