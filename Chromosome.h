#pragma once
#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <memory>
#include <vector>

class Chromosome
{
public:

	Chromosome(const int& size);
	~Chromosome(void);

	void SetChromosome( const int& index, const unsigned char& value );
	unsigned char GetChromosome( const int& index );

	void SetFitness( const double& value );
	double GetFitness() const;
	
	int GetSize() const;

private:

	std::vector<int> chr;

	int chrSize;
	double fitness;
};

#endif