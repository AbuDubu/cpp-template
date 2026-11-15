#include "clamp.h"

#include <gtest/gtest.h>

TEST(ClampInt, ValueInsideRangeIsUnchanged) {
    EXPECT_EQ(clamp_int(5, 0, 10), 5);
}

TEST(ClampInt, ValueBelowRangeBecomesLow) {
    EXPECT_EQ(clamp_int(-3, 0, 10), 0);
}

TEST(ClampInt, ValueAboveRangeBecomesHigh) {
    EXPECT_EQ(clamp_int(42, 0, 10), 10);
}
