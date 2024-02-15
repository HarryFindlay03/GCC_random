#include "optimizer.hpp"

int random_walk(std::vector<std::string>& applied_benchmarks, const std::string& program_name, int iterations, int n)
{
    // apply n random optimisations, record the time, if it is better record the optimisation set and go again
    // if not better than try from previous optimisation set

    // TODO optimisations on running can happen here - open a file to record data, then delete at the end rather than writing to secondary storage each time in run_given_string

    // getting available benchmarks and optimisations
    std::vector<std::string> benchmarks;
    std::vector<std::string> optimisations;

    if(!(read_benchmarks(DEFAULT_BENCHMARK_LIST_LOCATION, benchmarks)))
    {
        std::cout << "ERROR: reading benchmark file." << std::endl;
        return 0;
    }
    if(!(read_opt_file(DEFAULT_OPTIMISATIONS_LIST_LOCATION, optimisations)))
    {
        std::cout << "ERROR: reading optimisation file." << std::endl;
        return 0;
    }

    int i, best_index;
    double curr_exec_time, best_exec_time;
    std::string best_optimisations;

    for(i = 0, best_index = 0; i < iterations; i++)
    {
        // generating optimisations to apply
        std::string optimisation_string;
        generate_random_optimisation_string(optimisation_string, optimisations, n);

        /* apply and run optimisations on given program */

        // generating formatting benchmark string
        std::string benchmark_compile_string;
        if(!(format_benchmark_string(benchmark_compile_string, program_name, benchmarks)))
            return 0;

        // append the optimisations to benchmark compile string
        benchmark_compile_string.append(optimisation_string);

        // running which returns the speed of the program
        if((curr_exec_time = run_given_string(benchmark_compile_string, program_name)) == -1)
        {
            std::cout << "Execution failed: continuing." << std::endl;
            continue;
        }

        if((i == 0) || (curr_exec_time < best_exec_time))
        {
            best_index = i;
            best_exec_time = curr_exec_time;
            best_optimisations = optimisation_string;
        }

    }

    // TODO return applied benchmarks - split the string or rewrite the benchmarks function
        // rewritten function would return a vector of single benchmarks
        // another funciton would apply these to a given benchmark string (just append to the end)

    std::cout << "BEST EXECUTION TIME: " << best_exec_time << std::endl;
    std::cout << "BEST OPTIMISATION STRING: " << best_optimisations << std::endl;
    std::cout << "ITERATION AT: " << best_index << std::endl;

    return 1;
}