#ifndef RANDOM_OPTIMIZER_UTILS_HPP

#define RANDOM_OPTIMIZER_UTILS_HPP

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#define DEFAULT_BENCHMARK_COMPILE_STRING_LOCATION "data/benchmark_compile_strings.txt"
#define DEFAULT_BENCHMARK_LIST_LOCATION "data/benchmark_list.txt"
#define DEFAULT_OPTIMISATIONS_LIST_LOCATION "data/optimisations.txt"

#define DEFAULT_EXEC_OUTPUT_LOCATION "bin/tmp/"
#define DEFAULT_DATA_OUTPUT_LOCATION "data/tmp/tmpXX"

#endif


/**
 * @brief read file containing available optimisations from GCC
 * 
 * @param filename filename where information stored
 * @param optimisation_strings vector to fill
 * 
 * @return int 
 */
int read_opt_file(const std::string& filename, std::vector<std::string>& optimisation_strings);


/**
 * @brief reads the given file and fills the benchmarks vector with locations of polybench benchmarks
 * 
 * @param filename filename of benchmark list file
 * @param benchmarks vector to fill of all locations of benchmarks
 * 
 * @return int
 */
int read_benchmarks(const std::string& filename, std::vector<std::string>& benchmarks);


/**
 * @brief get program name from benchmark_list txt file provided from PolyBench
 * 
 * @param program_name string to fill with program name
 * @param benchmark_string string from PolyBench file
 * 
 * @return int
 */
int get_program_name(std::string& program_name, const std::string& benchmark_string);


/**
 * @brief generate list of optimisation strings to append to the end of a valid compile string
 * 
 * @param optimisations list of optimisations that can be applied
 * @param optimisation_string optimisation string to update with applied optimisations
 * @param num_to_apply number of optimisations to apply with optimisation string
 * 
 */
void generate_random_optimisation_string(std::string& optimisation_string, const std::vector<std::string>& optimisations, int num_to_apply);


/**
 * @brief compiles num_per_benchmark benchmark programs with random optimisations applied
 * 
 * @param benchmarks list of available benchmark programs
 * @param optimisations optimisations available to apply
 * @param num_optimisations number of optimisations
 * @param num_per_benchmark number of programs to compile per benchmark program
 * 
 * @return int
 */
int compile_and_log_all_benchmarks(const std::vector<std::string>& benchmarks, const std::vector<std::string>& optimisations, int num_optimisations, int num_per_benchmark);


/**
 * @brief runs all the benchmarks with logging once compilation has been completed
 * 
 * @param benchmarks available benchmarks to the program
 * @param benchmarks_to_test benchmarks to run and log
 * @param num_per_benchmark number of programs compiled per benchmark
 * 
 */
int run_benchmarks_with_logging(const std::vector<std::string>& benchmarks, const std::vector<std::string>& benchmarks_to_test, int num_per_benchmark);

/**
 * @brief format a compile string w.r.t passed benchmark to format. Output location specificed by DEFAULT_OUTPUT_LOCATION.
 * 
 * @param fmt_benchmark_string string to be updated.
 * @param benchmark_to_fmt specific benchmark to format.
 * @param benchmarks all benchmarks available.
 * 
 * @return int 
 */
int format_benchmark_string(std::string& fmt_benchmark_string, const std::string& benchmark_to_fmt, const std::vector<std::string>& benchmarks);

/**
 * @brief runs given string and returns the execution time
 * 
 * @param compile_string 
 * @param program_name
 * 
 * @return double 
 */
double run_given_string(const std::string& compile_string, const std::string& program_name);