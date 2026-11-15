#include "stats.hpp"

#include <benchmark/benchmark.h>

#include <cstddef>
#include <numeric>
#include <vector>

static void BM_Mean(benchmark::State& state) {
    std::vector<double> values(static_cast<std::size_t>(state.range(0)));
    std::iota(values.begin(), values.end(), 0.0);
    for (auto _ : state) {
        // DoNotOptimize stops the compiler from deleting a call whose result is unused.
        benchmark::DoNotOptimize(stats::mean(values));
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_Mean)->RangeMultiplier(8)->Range(64, 1 << 18);

BENCHMARK_MAIN();
