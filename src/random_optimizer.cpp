/* gcc-13 -I polybench-c-3.2/utilities -I polybench-c-3.2/linear-algebra/kernels/3mm polybench-c-3.2/utilities/polybench.c polybench-c-3.2/linear-algebra/kernels/3mm/3mm.c -o random_%d */

#include "random_optimizer.hpp"

/* TODO - not applying the optimisations correctly */

int main(int argc, char* argv[])
{
    /* parameters */
    int num_programs = 10;

    /* seeding rng */
    srand(time(0));

    /* generating benchmark compile strings */
    std::string benchmark_filename("data/benchmark_list.txt");
    std::string compile_filename("data/benchmark_compile_strings.txt");
    std::vector<std::string> benchmarks;

    read_benchmarks(benchmark_filename, benchmarks);

    /* WARNING: uncomment here requires misc_scripts.o to be passed to compiler*/
    // generate_benchmark_compile_strings(compile_filename, benchmarks);

    /* getting optimisations that we can apply */
    int num_optimisations;
    std::vector<std::string> optimisations;
    std::string optimisation_filename("data/optimisations.txt");
    if(!(num_optimisations = read_opt_file(optimisation_filename, optimisations)))
    {
        std::cout << "FILE READ ERROR!" << std::endl;
        std::exit(-1);
    }

    /* now we can apply random optimisations to the programs */
    compile_and_log_all_benchmarks(benchmarks, optimisations, 10, 10);

    return 1;
}