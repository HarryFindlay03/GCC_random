#include "optimizer.hpp"

int random_walk(std::vector<std::string>& applied_benchmarks, const std::string& program_name, int iterations, int n)
{
    // apply n random optimisations, record the time, if it is better record the optimisation set and go again
    // if not better than try from previous optimisation set

    // getting available benchmarks and optimisations
    std::vector<std::string> benchmarks;
    std::vector<std::string> optimisations;

    if(!(read_benchmarks(DEFAULT_BENCHMARK_COMPILE_STRING_LOCATION, benchmarks)))
    {
        std::cout << "ERROR: reading benchmark file." << std::endl;
        return 0;
    }
    if(!(read_opt_file(DEFAULT_OPTIMISATIONS_LIST_LOCATION, optimisations)))
    {
        std::cout << "ERROR: reading optimisation file." << std::endl;
        return 0;
    }

    int i;
    for(i = 0; i < iterations; i++)
    {
        // generating optimisations to apply
        std::string optimisation_string;
        generate_random_optimisation_string(optimisation_string, optimisations, n);

        /* apply and run optimisations on given program */

        // generating formatting benchmark string
        std::string benchmark_compile_string;
        if(!(format_benchmark_string(benchmark_compile_string, program_name, benchmarks)))
            return 0;

        // running which returns the speed of the program
        run_given_string(benchmark_compile_string, program_name);


        
    }
}