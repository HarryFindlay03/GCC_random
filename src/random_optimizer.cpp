/* gcc-13 -I polybench-c-3.2/utilities -I polybench-c-3.2/linear-algebra/kernels/3mm polybench-c-3.2/utilities/polybench.c polybench-c-3.2/linear-algebra/kernels/3mm/3mm.c -o random_%d */

#include "random_optimizer.hpp"

/* TODO - not applying the optimisations correctly */

int main(int argc, char* argv[])
{
    /* parameters */
    int num_programs = 10;

    /* seeding rng */
    srand(1234);

    /* generating benchmark compile strings */
    std::string benchmark_filename("data/benchmark_list.txt");
    std::string compile_filename("data/benchmark_compile_strings.txt");
    std::vector<std::string> benchmarks;

    read_benchmarks(benchmark_filename, benchmarks);

    std::string fmt_string;
    std::string benchmark_to_fmt = "2mm";

    std::vector<std::string> resulting_benchmarks;
    int status = random_walk(resulting_benchmarks, benchmark_to_fmt, 10, 20);
    if(!(status))
    {
        std::cout << "ERROR: in random walk." << std::endl;
        exit(EXIT_FAILURE);
    }

    /* WARNING: uncomment here requires misc_scripts.o to be passed to compiler*/
    // generate_benchmark_compile_strings(compile_filename, benchmarks);

    return 1;
}