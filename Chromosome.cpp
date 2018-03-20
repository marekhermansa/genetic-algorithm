#include "Chromosome.h"
#include <iostream>

Chromosome::Chromosome(const int& size)
{
	chrSize = size;
	for (int i = 0; i < chrSize; i++)
		chr.push_back(0);
}


Chromosome::~Chromosome(void)
{
}


// ustaw zawartosc chromosomu
void Chromosome::SetChromosome(const int& index, const unsigned char& value)
{
	if (index < 0 || index >= chrSize) return;

	chr[index] = value;
}


// zwroc zawartosc wybranego chromosomu
unsigned char Chromosome::GetChromosome(const int& index)
{
	unsigned char element = chr[index];
	return element;
}



// ustaw sprawnosc
void Chromosome::SetFitness(const double& value)
{
	fitness = value;
}


// zwroc sprawnosc chromosomu
double Chromosome::GetFitness() const
{
	return fitness;
}


// zwroc liczbe elementow (genow) chromosomu
int Chromosome::GetSize() const
{
	return chrSize;
}