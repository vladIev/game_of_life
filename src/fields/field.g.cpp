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

    for (const auto& cell : f.data()) {
        ASSERT_EQ(cell, 0);
    }
}