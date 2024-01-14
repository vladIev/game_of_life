#include "field.hpp"

#include <gtest/gtest.h>

using namespace life;
TEST(field, constructor)
{
    const size_t width = 5;
    const size_t height = 10;
    Field f(width, height);

    EXPECT_EQ(f.width(), width);
    EXPECT_EQ(f.height(), height);

    for (const auto& rows : f.data()) {
        for (const auto& cell : rows) {
            ASSERT_EQ(cell, 0);
        }
    }
}