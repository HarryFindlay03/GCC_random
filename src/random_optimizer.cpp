/* gcc-13 -I polybench-c-3.2/utilities -I polybench-c-3.2/linear-algebra/kernels/3mm polybench-c-3.2/utilities/polybench.c polybench-c-3.2/linear-algebra/kernels/3mm/3mm.c -o random_%d */

#include "random_optimizer.hpp"

/* TODO - not applying the optimisations correctly */

int main(int argc, char* argv[])
{
    /* parameters */
    int num_programs = 10;

    /* seeding rng */
    srand(RANDOM_SEED);

    /* generating benchmark compile strings */
    // std::string benchmark_filename("data/benchmark_list.txt");
    // std::string compile_filename("data/benchmark_compile_strings.txt");
    // std::vector<std::string> benchmarks;

    // read_benchmarks(benchmark_filename, benchmarks);

    // std::string fmt_string;
    // std::string benchmark_to_fmt = "2mm";

    // std::vector<std::string> resulting_benchmarks;
    // int status = random_walk(resulting_benchmarks, benchmark_to_fmt, 10, 20);
    // if(!(status))
    // {
    //     std::cout << "ERROR: in random walk." << std::endl;
    //     exit(EXIT_FAILURE);
    // }

    // testing generating random population
    const size_t population_size = 7;
    const size_t solution_length = 15;
    const size_t tournament_size = 3;

    std::vector<std::string> optimisations;
    std::vector<std::string> benchmarks;
    read_opt_file(DEFAULT_OPTIMISATIONS_LIST_LOCATION, optimisations);
    read_benchmarks(DEFAULT_BENCHMARK_LIST_LOCATION, benchmarks);

    std::string benchmark_to_fmt = "correlation";

    auto pop = create_random_population(population_size, solution_length, optimisations.size());
    auto ordering  = population_fitness_order(pop, optimisations, benchmarks, benchmark_to_fmt, solution_length);
    for(auto val : ordering)
        std::cout << val << '\t';
    std::cout << std::endl;

    // tournament test
    auto pool = create_tournament_pool(pop, solution_length, tournament_size);

    for(auto pool_v : pool)
        std::cout << pool_v << '\t';
    std::cout << std::endl;

    std::cout << "TOURNAMENT WINNER: " << get_tournament_winner(pool, ordering) << std::endl;

    /* WARNING: uncomment here requires misc_scripts.o to be passed to compiler*/
    // generate_benchmark_compile_strings(compile_filename, benchmarks);

    return 1;
}