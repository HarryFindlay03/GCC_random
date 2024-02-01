#include "random_optimizer_utils.hpp"

int main()
{
    /* running the programs with logging */
    std::string benchmark_filename("data/benchmark_list.txt");
    std::vector<std::string> benchmarks;
    read_benchmarks(benchmark_filename, benchmarks);

    int num_per_benchmark = 10;
    run_benchmarks_with_logging(benchmarks, num_per_benchmark);

    return 0;
}