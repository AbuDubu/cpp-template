#include "stats.hpp"

#include <gtest/gtest.h>

#include <array>
#include <span>

TEST(Mean, AveragesValues) {
    const std::array<double, 4> v{1.0, 2.0, 3.0, 4.0};
    EXPECT_DOUBLE_EQ(stats::mean(v), 2.5);
}

TEST(Mean, SingleValueIsItself) {
    const std::array<double, 1> v{7.5};
    EXPECT_DOUBLE_EQ(stats::mean(v), 7.5);
}

TEST(Mean, EmptySpanIsZero) {
    EXPECT_DOUBLE_EQ(stats::mean(std::span<const double>{}), 0.0);
}
