#pragma once
#ifndef POPULATION_H
#define POPUALATION_H

#include <vector>
#include "Chromosome.h"

const double inf = 9999999999999;
const double pi = 3.1415926;

class Population
{
public:

	Population(void);
	~Population(void);

	void CreateRandomPopulation(const int& size);
	double EvaluatePopulation(float& bx, float& by);

	void Mutation(const int& index, const int& mutationRatio);
	void Crossover(const int& index1, const int& index2, const int& point);
	
	void SetChromosomeSize(const int& size);
	double CalcChromosomeFitness(const int& index, float& xv, float& yv);
	double GetChromosomeFitness(const int& index) const;
	void CopyChromosome(const int& source, const int& dest);

private:

	Chromosome* CreateRandomChromosome();
	
	std::string GetXstring(Chromosome* chr);
	std::string GetYstring(Chromosome* chr); 
	
	float GetFloat32_IEEE754(std::string Binary);
	int Binary32ToHex(std::string Binary);
	
	double CalculateFitnessFunction(const float& x, const float& y);

private:

	std::vector<Chromosome*> pop;
	int chrSize;
};

#endif