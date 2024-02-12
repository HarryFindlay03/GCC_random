#include "random_optimizer_utils.hpp"

int main()
{
    /* running the programs with logging */
    std::string benchmark_filename("data/benchmark_list.txt");
    std::vector<std::string> benchmarks;
    read_benchmarks(benchmark_filename, benchmarks);

    int num_per_benchmark = 10;
    std::vector<std::string> benchmarks_to_test = {"2mm", "correlation"};

    run_benchmarks_with_logging(benchmarks, benchmarks_to_test, num_per_benchmark);

    return 0;
}