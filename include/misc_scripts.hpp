#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
 * @brief generate benchmark compile strings from benchmarks vector
 * 
 * @param compile_filename 
 * @param benchmarks 
 */
void generate_benchmark_compile_strings(const std::string& compile_filename, const std::vector<std::string>& benchmarks);