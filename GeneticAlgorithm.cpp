#include "GeneticAlgorithm.h"

#include <iostream>
#include <iomanip>
#include <sstream>

GeneticAlgorithm::GeneticAlgorithm(void)
{
	// ustaw wartosc domyslna
	bestFitness = inf;
}


GeneticAlgorithm::~GeneticAlgorithm(void)
{
}


// zainicjalizuj wartosci parametrow, generuj populacje poczatkowa
void GeneticAlgorithm::Load(const int& cratio, const int& mratio,
	const int& psize, const int& gener, const int& csize, const int& ssize,
	const std::string& path)
{
	SetParameters(cratio, mratio, psize, gener, csize, ssize);
	CreatePopulation();
	record.Open(path.c_str());
}


// ustaw dane wartosci parametrow
void GeneticAlgorithm::SetParameters(const int& cratio, const int& mratio,
	const int& psize, const int& gener, const int& csize, const int& ssize)
{
	numberGenerations = gener;

	populationSize = psize;
	chromosomeSize = csize;

	crossoverRatio = cratio;
	mutationRatio = mratio;
	selection_size = ssize;
}


void GeneticAlgorithm::CreatePopulation()
{
	pop.CreateRandomPopulation(populationSize);
}


// wykonaj algorytm
void GeneticAlgorithm::Start()
{
	for (int i = 0; i < numberGenerations; i++)
	{
		RecordResult(Evaluate(), i);
		Select();
		Crossover();
		Mutate();
	}
}


// zapisz statystyki do pliku lub wyswietl w konsoli
void GeneticAlgorithm::RecordResult(const double& result,
	const int& gener)
{
	// zapis do pliku
	std::stringstream ss;
	ss << gener << " " << best_x << " " << best_y << " " << result;
	record.Write((char*)ss.str().c_str());

	// wydruk w konsoli
	int precision = 7;
	std::cout << "generacja = " << std::setw(6) << gener
		<< " x = " << std::fixed << std::setprecision(precision) << std::setw(precision + 1) << best_x
		<< " y = " << std::fixed << std::setprecision(precision) << std::setw(precision + 1) << best_y
		<< " f(x,y) = " << std::setw(precision + 1) << bestFitness
		<< std::endl;
}


// ocen sprawnosc chromosomow w populacji
double GeneticAlgorithm::Evaluate()
{
	float bx = -1;
	float by = -1;

	double best = pop.EvaluatePopulation(bx, by);

	if (best < bestFitness)
	{
		bestFitness = best;
		best_x = bx;
		best_y = by;
	}

	return bestFitness;
}


// wybierz chromosomy z populacji na podstawie ich sprawnosci
void GeneticAlgorithm::Select()
{

	int i = 0;

	while (i < selection_size)
	{
		// wybierz pare chromosomow do porownania
		int index1 = rand() % populationSize;
		int index2 = rand() % populationSize;

		while (index1 == index2)
		{
			index2 = rand() % populationSize;
		}

		double fitness1 = pop.GetChromosomeFitness(index1);
		double fitness2 = pop.GetChromosomeFitness(index2);

		// celem jest znalezienie takich x i y, ktore minimalizuja funkcje
		// stad im wieksza zwrocona wartosc, tym mniejsza sprawnosc
		if (fitness1 > fitness2)
		{
			// skopiuj elementy chromosomu 1 do chromosomu 2
			pop.CopyChromosome(index2, index1);
		}
		else
		{
			// skopiuj elementy chromosomu 2 do chromosomu 1
			pop.CopyChromosome(index1, index2);
		}

		i++;
	}
}


// zastosuj operator krzyzowania do wyboru par chromosomow
void GeneticAlgorithm::Crossover()
{
	for (int i = 0; i < populationSize; i++)
	{
		int r = rand() % 100;

		if (r < crossoverRatio)
		{
			// wybierz losowo pare chromosomow
			int index1 = rand() % populationSize;
			int index2 = rand() % populationSize;

			while (index1 == index2)
			{
				index2 = rand() % populationSize;
			}

			if (index1 > index2)
			{
				int tmp = index1;
				index1 = index2;
				index2 = tmp;
			}
			// uzyskaj punkt rozciecia
			int point1 = rand() % chromosomeSize;

			// wykonaj krzyzowanie z jednym puktem przeciecia
			pop.Crossover(index1, index2, point1);
		}
	}
}


// przeprowadz mutacje na wybranych chromosomach
void GeneticAlgorithm::Mutate()
{
	for (int i = 0; i < populationSize; i++)
	{
		int r = rand() % 100;

		if (r < mutationRatio)//
		{
			pop.Mutation(i, mutationRatio);
		}
	}
}