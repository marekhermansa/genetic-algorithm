#include <time.h>
#include <sstream>

#include "GeneticAlgorithm.h"
#include "Record.h"

const std::string& path = ".\\log.txt";

// parametry ogolne
const int number_generations = 1000;
const int population_size = 500;
const int chromosome_size = 32;

// paramentry dot. operatorow
const int crossover_ratio = 50;
const int mutation_ratio = 20;
const int selection_size = population_size / 10;


int main(int argc, char* argv[])
{
	srand((int)time(NULL));

	GeneticAlgorithm genetic_algorithm;

	genetic_algorithm.Load(crossover_ratio, mutation_ratio,
		population_size, number_generations, chromosome_size,
		selection_size, path);

	genetic_algorithm.Start();

	system("pause");

	return 0;
}

