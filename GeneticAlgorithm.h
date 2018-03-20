#pragma once
#ifndef GENETICALGORITHM_H
#define GENETICALGORTIHM_H

#include "Population.h"
#include "Record.h"

class GeneticAlgorithm
{
public:

	GeneticAlgorithm(void);
	~GeneticAlgorithm(void);

	void Load( const int& cratio, const int& mratio, const int& psize, 
		const int& iter, const int& csize, const int& ssize,
		const std::string& path);
	void Start();

private:

	void CreatePopulation();
	double Evaluate();

	void Crossover();
	void Mutate();
	void Select();

	void SetParameters(const int& cratio, const int& mratio, 
		const int& psize, const int& iter, const int& csize, 
		const int& ssize );

	void RecordResult(const double& result, const int& iter);

private:

	int numberGenerations;

	int mutationRatio;
	int crossoverRatio;

	int populationSize;
	int chromosomeSize;
	int selection_size;
	
	double bestFitness;
	int bestFitnessIndex;
	float best_x;
	float best_y;

	Population pop;
	Record record;
};

#endif