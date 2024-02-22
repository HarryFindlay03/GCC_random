#include "random_optimizer_utils.hpp"

#include <algorithm>
#include <random>
#include <numeric>

/* STANDARD EA FUNCTIONS */

std::vector<size_t> create_random_population(int population_size, int solution_length, int num_optimisations_available);

double solution_fitness(const std::vector<size_t>& population, const std::vector<std::string>& optimisations, const std::vector<std::string>& benchmarks, std::string& benchmark_to_fmt, const int solution_index, const int solution_length);

std::vector<size_t> population_fitness_order(const std::vector<size_t>& population, const std::vector<std::string>& optimisations, const std::vector<std::string>& benchmarks, std::string& benchmark_to_fmt, const int solution_length);

/* END STANDARD EA FUNCTIONS */

/* TOURNAMENT FUNCTIONS */

std::vector<size_t> create_tournament_pool(const std::vector<size_t>& population, int solution_length, int tournament_size);

size_t get_tournament_winner(const std::vector<size_t>& pool, const std::vector<size_t>& ordering);

/* END TOURNAMENT FUNCTIONS */


/* MUTATION FUNCTIONS */

void swap_mutation(std::vector<size_t>& solution, int solution_length, double mutation_rate);

/* END MUTATION FUNCTIONS */

