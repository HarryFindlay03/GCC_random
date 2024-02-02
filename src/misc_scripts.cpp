#include "misc_scripts.hpp"


void generate_benchmark_compile_strings(const std::string& compile_filename, const std::vector<std::string>& benchmarks)
{
    /* opening output file */
    std::ofstream output_file(compile_filename);
    if(!(output_file.is_open()))
    {
        std::cout << "ERROR OPENING FILE!" << std::endl;
        std::exit(-1);
    }

    int i, n;
    n = benchmarks.size();
    for(i = 0; i < n; i++)
    {
        std::string default_string("gcc-13 -I polybench-c-3.2/utilities");

        /* header file location */
        std::string benchmark_compile_string;
        benchmark_compile_string.append(" -I ");

        // removing final bit of string
        std::string temp = benchmarks[i];
        int i, j;
        for(i = temp.size() - 1; i >= 0; i--)
        {
            if(temp[i] == '/')
                break;
        }

        // finding program name
        for(j = temp.size() - 1; j >= 0; j--)
        {
            if(temp[j] == '.')
                break;
        }
        std::string program_name = temp.substr(i+1, (j - i - 1));

        // formatting program name
        benchmark_compile_string.append(temp.substr(0, i));
        benchmark_compile_string.append(" polybench-c-3.2/utilities/polybench.c ");
        benchmark_compile_string.append(temp);
        benchmark_compile_string.append(" -DPOLYBENCH_TIME -o bin/random_optimizer_output/" + program_name + "/" + program_name + "_");

        default_string.append(benchmark_compile_string);
        output_file << default_string << std::endl;

    }

    output_file.close();

    return;
}