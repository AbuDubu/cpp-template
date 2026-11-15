#include "stats.hpp"

#include <numeric>

namespace stats {

double mean(std::span<const double> values) {
    if (values.empty()) {
        return 0.0;
    }
    const double sum = std::accumulate(values.begin(), values.end(), 0.0);
    return sum / static_cast<double>(values.size());
}

} // namespace stats
