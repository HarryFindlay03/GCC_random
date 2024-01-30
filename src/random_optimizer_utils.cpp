#include "random_optimizer_utils.hpp"


int read_opt_file(const std::string& filename, std::vector<std::string>& optimisation_strings)
{
    /* read optimisations file and update vector reference */
    int num_optimisations = 0;
    std::string line;
    std::ifstream opt_file(filename);

    if(opt_file.is_open())
    {
        while(getline(opt_file, line))
        {
            optimisation_strings.push_back(line);
            num_optimisations++;
        }
    } else { return 0; }

    return num_optimisations;
}


void apply_optimisation(std::string& compile_string, const std::vector<std::string>& optimisation_strings, int num_optimisations)
{
    /* random choice in optimisation strings*/
    int ran_choice = rand() % num_optimisations + 1;
    std::string to_apply = optimisation_strings[ran_choice] + " ";

    /* append to compile string */
    compile_string.append(to_apply);

    return;
}


int get_program_name(const std::string& benchmark_string, std::string& program_name)
{
    int i, j;
    
    // find last '/'
    for(i = benchmark_string.size(); i >= 0; --i)
    {
        if(benchmark_string[i] == '/')
            break;
    }

    // find last '.'
    for(j = benchmark_string.size(); j >= 0; --j)
    {
        if(benchmark_string[j] == '.')
            break;
    }

    program_name = benchmark_string.substr(i + 1, (j - i - 1));

    if(i == 0 || j == 0) return 0;
    return 1;
}


void generate_random_optimisation_string(const std::vector<std::string>& optimisations, std::string& optimisation_string, int num_to_apply)
{
    /* random number */
    int ran;

    int i, n;
    n = optimisations.size();

    for(i = 0; i < n; i++)
    {
        ran = rand() % n + 1;
        optimisation_string.append(" " + optimisations[ran]);
    }

    return;
}


int compile_and_log_all_benchmarks(const std::vector<std::string>& benchmarks, const std::vector<std::string>& optimisations, int num_optimisations_to_apply, int num_per_benchmark)
{
    /* read benchmark compile strings */
    std::vector<std::string> benchmark_compile_strings;
    std::ifstream my_file("data/benchmark_compile_strings.txt");

    std::string line;
    if(my_file.is_open())
    {
        while(getline(my_file, line))
        {
            benchmark_compile_strings.push_back(line);
        }
    } else return 0;


    std::string program_name;
    std::string optimisation_string;
    int i, j, n;
    n = benchmarks.size();
    for(i = 0; i < n; i++)
    {
        // get compile string for benchmark
        if(!(get_program_name(benchmarks[i], program_name)))
        {
            std::cout << "ERROR READING PROGRAM NAME" << std::endl;
            return 0;
        }

        // create correct folder structure
        std::string create_folder_cmd("mkdir bin/random_optimizer_output/" + program_name);
        std::system(create_folder_cmd.c_str());

        // generate number of programs per benchmark
        for(j = 0; j < num_per_benchmark; j++)
        {
            // get random optimisation string
            generate_random_optimisation_string(optimisations, optimisation_string, num_optimisations_to_apply);

            // compile and execute random optimisation string
            std::string exec_string = benchmark_compile_strings[i] + std::to_string(j) + optimisation_string;
            std::system(exec_string.c_str());

            /* TODO - log optimisations in the correct place */
        }
    }        

    return 1;
}


// ensure compile string is formatted correctly
void compile_program(std::string& compile_string, int program_number)
{
    int buff_size = compile_string.size() + std::to_string(program_number).size() + 2;

    char buff[buff_size];
    std::snprintf(buff, sizeof(buff), compile_string.c_str(), program_number);
    std::system(buff);

    /* output buff to a file */
    std::ofstream output_file;
    output_file.open("data/compile_strings.txt", std::ios::app);
    output_file << program_number << ":" << buff << std::endl;
    output_file.close();

    return;
}


void run_programs(int num_programs)
{
    int i;
    for(i = 0; i < num_programs; i++)
    {
        char buff[100];
        std::snprintf(buff, sizeof(buff), "time ./bin/random_%d", i);

        std::system(buff);
    }

    return;
}