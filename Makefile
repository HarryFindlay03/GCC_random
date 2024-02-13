CC = g++-13

all: random_optimizer

clear_bin:
	rm -rf bin/random_optimizer_output/*

generate_folder_structure:
	if [ ! -d build ]; then mkdir -p build; fi; if [ ! -d bin ]; then mkdir -p bin; fi; if [ ! -d bin/random_optimizer_output ]; then mkdir -p bin/random_optimizer_output; fi; if [ ! -d data/random_optimizer_output ]; then mkdir -p data/random_optimizer_output; fi; if [ ! -d bin/tmp ]; then mkdir -p bin/tmp; fi

misc_scripts.o:
	g++-13 -c -I include/ src/misc_scripts.cpp -o build/misc_scripts.o

random_optimizer_utils.o:
	g++-13 -c -I include/ src/random_optimizer_utils.cpp -o build/random_optimizer_utils.o

random_optimizer.o:
	g++-13 -c -I include/ src/random_optimizer.cpp -o build/random_optimizer.o

random_optimizer: generate_folder_structure clear_bin random_optimizer_utils.o random_optimizer.o
	g++-13 -I include/ build/random_optimizer_utils.o build/random_optimizer.o -o random_optimizer

run_programs.o:
	g++-13 -c -I include/ src/run_programs.cpp -o build/run_programs.o

run_programs: random_optimizer_utils.o run_programs.o
	g++-13 -I include/ build/random_optimizer_utils.o build/run_programs.o -o run_programs

