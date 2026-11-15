#include "clamp.h"
#include "stats.hpp"

#include <array>
#include <cstdio>

int main() {
    const std::array<double, 4> samples{1.0, 2.0, 3.0, 4.0};
    std::printf("mean = %.2f\n", stats::mean(samples));
    std::printf("clamp_int(42, 0, 10) = %d\n", clamp_int(42, 0, 10));
    return 0;
}
