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


int read_benchmarks(const std::string& benchmark_filename, std::vector<std::string>& benchmarks)
{
    std::string line;
    std::ifstream benchmark_file(benchmark_filename);

    if(benchmark_file.is_open())
    {
        while(getline(benchmark_file, line))
        {
            benchmarks.push_back(line);
        }
    } else return 0;

    benchmark_file.close();
    return 1;
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

    for(i = 0; i < num_to_apply; i++)
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


    int i, j, n;
    n = benchmarks.size();
    for(i = 0; i < n; i++)
    {
        std::string program_name;
        // get compile string for benchmark
        if(!(get_program_name(benchmarks[i], program_name)))
        {
            std::cout << "ERROR READING PROGRAM NAME" << std::endl;
            return 0;
        }

        // create correct folder structure for program output
        std::string create_folder_cmd("mkdir bin/random_optimizer_output/" + program_name);
        std::system(create_folder_cmd.c_str());

        // create output file for each benchmark program
        std::string output_filename("data/random_optimizer_output/" + program_name + ".txt");
        std::ofstream output_file(output_filename);

        if(!output_file.is_open())
        {
            std::cout << "FILE OPEN ERROR!" << std::endl;
            return 0;
        }

        // generate number of programs per benchmark
        for(j = 0; j < num_per_benchmark; j++)
        {
            // get random optimisation string
            std::string optimisation_string;
            generate_random_optimisation_string(optimisations, optimisation_string, num_optimisations_to_apply);

            // compile and execute random optimisation string
            std::string exec_string = benchmark_compile_strings[i] + std::to_string(j) + optimisation_string;
            std::system(exec_string.c_str());

            // logging to output file
            output_file << j << ": " << optimisation_string << std::endl;
        }

        output_file.close();
    }        

    return 1;
}


int run_benchmarks_with_logging(const std::vector<std::string>& benchmarks, const std::vector<std::string>& benchmarks_to_test, int num_per_benchmark)
{
    /* create tmp folder - this will be deleted at the end of the run */
    std::system("mkdir tmp");

    std::string program_name;

    int i, j, x, n, test_n;
    n = benchmarks_to_test.size();
    test_n = benchmarks.size();

    for(i = 0; i < n; i++)
    {
        /* checking benchmarks_to_test name is valid */
        std::string curr_benchmark = benchmarks_to_test[i];
        int valid = 0;

        for(x = 0; x < test_n; x++)
        {
            if (!(get_program_name(benchmarks[x], program_name)))
            {
                std::cout << "ERROR READING PROGRAM NAME." << std::endl;
                return 0;
            }

            if(program_name == curr_benchmark)
            {
                valid = 1;
                break;
            }
        }

        if(!valid)
        {
            std::cout << curr_benchmark << " is not a valid benchmark name. skipping." << std::endl;
            continue;
        }

        // opening the output file
        std::string output_filename = "data/random_optimizer_output/" + program_name + "_logging.txt";
        std::ofstream my_output_file(output_filename);

        if(!my_output_file.is_open())
        {
            std::cout << "PERFORMANCE LOGGING: FILE ERROR." << std::endl;
            return 0;
        }
        my_output_file << "program_number,exec_time" << std::endl;

        for(j = 0; j < num_per_benchmark; j++)
        {
            // formatting
            std::string fmt_program_name = program_name + "_" + std::to_string(j);
            std::string exec_string = "bin/random_optimizer_output/" + program_name + "/" + fmt_program_name;
            exec_string.append(" > tmp/" + fmt_program_name + ".txt");

            // running
            std::system(exec_string.c_str());

            /* collect logging data */
            std::string input_filename = "tmp/" + fmt_program_name + ".txt";
            std::ifstream my_input_file(input_filename);

            if(!my_input_file.is_open())
            {
                std::cout << "PERFORMANCE LOGGING: FILE ERROR." << std::endl;
                return 0;
            }

            std::string line;
            while(getline(my_input_file, line))
            {
                my_output_file << j << "," << line << std::endl;
            }

            my_input_file.close();
        }

        my_output_file.close();
    }

    /* TODO - collect the logging data */


    std::system("rm -rf tmp");

    return 1;
}