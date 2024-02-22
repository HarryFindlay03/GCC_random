#include "evolutionary.hpp"

/* STANDARD EA FUNCTIONS */

std::vector<size_t> create_random_population(int population_size, int solution_length, int num_optimisations_available)
{
    std::vector<size_t> pop(population_size * solution_length);


    int i, j;
    for(i = 0; i < (population_size * solution_length);)
    {
        auto curr = generate_random_optimisation_vector(num_optimisations_available, solution_length);

        j = 0;
        for(auto val : curr)
            pop[i + (j++)] = val;
        
        i += solution_length;
    }

    return pop;
}


double solution_fitness(const std::vector<size_t>& population, const std::vector<std::string>& optimisations, const std::vector<std::string>& benchmarks, std::string& benchmark_to_fmt, const int solution_index, const int solution_length)
{
    /* constructing string */

    // find correct position within population
    std::vector<int> sol(population.begin() + (solution_index * solution_length), population.begin() + (solution_index * solution_length) + solution_length);

    std::string benchmark_string;
    format_benchmark_string(benchmark_string, benchmark_to_fmt, benchmarks);

    //append optimisations
    benchmark_string.append(optimisation_int_vector_to_string(sol, optimisations));

    double res = run_given_string(benchmark_string, benchmark_to_fmt);

    return res;
}


std::vector<size_t> population_fitness_order
(const std::vector<size_t>& population, const std::vector<std::string>& optimisations, const std::vector<std::string>& benchmarks, std::string& benchmark_to_fmt, const int solution_length)
{
    int i, n;

    n = population.size() / solution_length;
    std::vector<double> fit_vec(n);

    // benchmark each string in population
    for(i = 0; i < n; i++)
        fit_vec[i] = solution_fitness(population, optimisations, benchmarks, benchmark_to_fmt, i, solution_length);

    std::vector<size_t> idx(n);
    for(i = 0; i < n; i++)
        idx[i] = i;

    // sort indexes based on comparing values in v
    std::stable_sort(idx.begin(), idx.end(), [&fit_vec](size_t a, size_t b){return fit_vec[a] < fit_vec[b];});

    return idx;
}


void replace_worst_solution(std::vector<size_t>& population, const std::vector<size_t>& population_order, const std::vector<size_t>& new_sol, int solution_length)
{
    // index of worst
    size_t worst_idx = population.back();

    // replace population values with new solution
    int i, j;
    for(i = worst_idx, j = 0; i < solution_length; i++, j++)
        population[i] = new_sol[j];

    return;
}


/* END STANDARD EA FUNCTIONS */


/* TOURNAMENT FUNCTIONS */


std::vector<size_t> create_tournament_pool(const std::vector<size_t>& population, int solution_length, int tournament_size)
{
    std::vector<size_t> ran_list(population.size() / solution_length);
    std::iota(ran_list.begin(), ran_list.end(), 0);

    // shuffling ran_list
    std::shuffle(ran_list.begin(), ran_list.end(), std::default_random_engine(RANDOM_SEED));

    // creating and returning pool
    std::vector<size_t> pool(ran_list.begin(), ran_list.begin() + tournament_size);
    return pool;
}


size_t get_tournament_winner(const std::vector<size_t>& pool, const std::vector<size_t>& ordering)
{
    int i, j, pool_n, ordering_n;
    pool_n = pool.size();
    ordering_n = ordering.size();

    int best_pos = ordering_n;
    size_t best_pool = pool[0];

    for(i = 0; i < pool_n; i++)
    {
        for(j = 0; j < ordering_n; j++)
        {
            if(pool[i] == ordering[j])
            {
                if(j < best_pos)
                {
                    best_pos = j;
                    best_pool = pool[i];
                }
                break;
            }
        }
    }

    return best_pool;
}


/* END TOURNAMENT FUNCTIONS */


/* MUTATION FUNCTIONS */


void swap_mutation(std::vector<size_t>& solution, int solution_length, double mutation_rate)
{
    // swapping two random positions within solution
    double ran = (double)rand() / (double)RAND_MAX;

    if(mutation_rate > ran)
    {
        int pos1 = rand() % solution_length;
        int pos2 = rand() % solution_length;

        size_t temp = solution[pos1];
        solution[pos1] = solution[pos2];
        solution[pos2] = temp;
    }

    return;
}


/* END MUTATION FUNCTIONS*/