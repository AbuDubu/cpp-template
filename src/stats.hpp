#pragma once

#include <span>

namespace stats {

// Arithmetic mean of the values. Returns 0.0 for an empty span.
double mean(std::span<const double> values);

} // namespace stats
