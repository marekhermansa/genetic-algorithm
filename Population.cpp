#include "Population.h"
#include <bitset>
#include <iostream>
#include <iomanip>      // std::setw
#include <math.h>


Population::Population(void)
{
	// ustaw domyslny rozmiar chromosomu
	chrSize = 64;
}


Population::~Population(void)
{
	int size = (int)pop.size();

	// usun wskazniki na chromosomy
	for (int i = 0; i < size; i++)
	{
		Chromosome* chr = pop.at(i);

		if (chr)
		{
			delete chr;
		}
	}

	pop.clear();
}


// stworz poczatkowa losowa populacje chromosomow
void Population::CreateRandomPopulation(const int& size)
{
	for (int i = 0; i < size; i++)
	{
		Chromosome* chr = CreateRandomChromosome();
		pop.push_back(chr);
	}
}


// zastosuj krzyzowanie z jednym punktem przeciecia
void Population::Crossover(const int& index1, const int& index2, const int& point)
{
	if (point < 0 || point >= chrSize) return;

	Chromosome* chr1 = pop.at(index1);
	Chromosome* chr2 = pop.at(index2);

	for (int i = point; i < chrSize; i++)
	{
		unsigned char v1 = chr1->GetChromosome(i);
		unsigned char v2 = chr2->GetChromosome(i);

		chr1->SetChromosome(index1, v2);
		chr2->SetChromosome(index1, v1);
	}
}


// zastosuj mutacje do wybranego chromosomu, czesci x lub czesci y
void Population::Mutation(const int& index, const int& mutationRatio)
{
	Chromosome* chr = pop.at(index);

		bool xpart = rand() % 2 < 1 ? true : false;

		int start = xpart ? 0 : chrSize / 2;
		int end = xpart ? chrSize / 2 : chrSize;

		for (int i = start; i < end; i++)
		{
			int r = rand() % 100;

			if (r < mutationRatio)
			{
				unsigned char value = chr->GetChromosome(i);
				value = rand() % 100 < 50 ? 1 : 0;
				chr->SetChromosome(i, value);
			}
		}
}


// ocen sprawnosc populacji
double Population::EvaluatePopulation(float& bx, float& by)
{
	double totalFitness = 0.0;
	double aveFitness = 0.0;
	double bestFitness = inf;
	int bestFitnessIndex = 0;

	for (int i = 0; i < (int)pop.size(); i++)
	{
		float x, y;

		double fitness = CalcChromosomeFitness(i, x, y);
		Chromosome* chr = pop.at(i);
		chr->SetFitness(fitness);

		//chr->Print( i );

		// zapamietaj najlepsze rozwiazanie
		if (i == 0) bestFitness = fitness;

		if (fitness < bestFitness)
		{
			bestFitness = fitness;
			bestFitnessIndex = i;
			bx = x;
			by = y;
		}
	}

	return bestFitness;
}


// utworz chromosom o losowych wartosciach
Chromosome* Population::CreateRandomChromosome()
{
	Chromosome* chr = new Chromosome(chrSize);

	for (int i = 0; i < chr->GetSize(); i++)
	{
		unsigned char value = rand() % 10 < 5 ? 0 : 1;
		chr->SetChromosome(i, value);
	}

	return chr;
}


double Population::CalcChromosomeFitness(const int& index, float& xv, float& yv)
{
	// uzyskaj elementy chromosomu
	Chromosome* chr = pop.at(index);

	// umiesc pierwsze 32 bity (czesc x) w string
	std::string xstr = GetXstring(chr);

	// uzyskaj wartosc x poprzez konwersje z IEEE 754 do liczby dziesietnej
	float x = GetFloat32_IEEE754(xstr);

	// umiesc kolejne 32 bity  (czesc y) do string
	std::string ystr = GetYstring(chr);

	// uzyskaj wartosc y poprzez konwersje z IEEE 754 do liczby dziesietnej
	float y = GetFloat32_IEEE754(ystr);

	double fitness = CalculateFitnessFunction(x, y);

	// zwroc sprawnosc chromosomu
	xv = x;
	yv = y;
	return fitness;
}


// oblicz sprawnosc, f(x,y)
double Population::CalculateFitnessFunction(const float& x, const float& y)
{
	// McCormick function
	// global min: f(−0.5471975602214,−1.547197559268) = −1.913222954981
	double fitness = sin(x + y) + (x - y)*(x - y) - 1.5*x + 2.5*y + 1;

	double maxX = 4.0;
	double minX = -1.5;
	double maxY = 4.0;
	double minY = -3.0;
	if (x > maxX || x < minX || y > maxY || y < minY)
	{
		return fitness * 1.2;
	}
	else
	{
		return fitness;
	}
}


// przekonweruj 32-bitowy ciag na liczbe dziesietna
// kodowanie IEEE 754 dla 32-bitowego ciagu
float Population::GetFloat32_IEEE754(std::string Binary)
{
	int HexNumber = Binary32ToHex(Binary);

	bool negative = !!(HexNumber & 0x80000000);
	int  exponent = (HexNumber & 0x7f800000) >> 23;
	int sign = negative ? -1 : 1;

	// odejmij 127 z wykladnika
	exponent -= 127;

	// przekonwertuj mantyse na wartosc dziesietna 
	// uzywaja ostatnich 23 bitow
	int power = -1;
	float total = 0.0;
	for (int i = 0; i < 23; i++)
	{
		int c = Binary[i + 9] - '0';
		total += (float)c * (float)pow(2.0, power);
		power--;
	}
	total += 1.0;

	float value = sign * (float)pow(2.0, exponent) * total;

	return value;
}


// przekonwertuj 32-bitowy ciag na liczbe szesnastkowa
int Population::Binary32ToHex(std::string Binary)
{
	std::bitset<32> set(Binary);
	int hex = set.to_ulong();

	return hex;
}


// uzyskaj czesc x chromosomu
std::string Population::GetXstring(Chromosome* chr)
{
	std::string xstr;

	for (int i = 0; i < chrSize / 2; i++)
	{
		unsigned char value = chr->GetChromosome(i);
		xstr.append(value == 0 ? "0" : "1");
	}

	return xstr;
}


// uzyskaj czesc y chromosomu
std::string Population::GetYstring(Chromosome* chr)
{
	std::string ystr;
	int start = chrSize / 2;

	for (int i = start; i < chrSize; i++)
	{
		unsigned char value = chr->GetChromosome(i);
		ystr.append(value == 0 ? "0" : "1");
	}

	return ystr;
}


// dlugosc chromosomu
void Population::SetChromosomeSize(const int& size)
{
	chrSize = size;
}


double Population::GetChromosomeFitness(const int& index) const
{
	Chromosome* chr = pop.at(index);

	return chr->GetFitness();
}


// skopiuj zawartosc jednego chromosomu
void Population::CopyChromosome(const int& source, const int& dest)
{
	// uzyskaj chromosomy
	Chromosome* chr1 = pop.at(source);
	Chromosome* chr2 = pop.at(dest);

	// skopiuj zawartosc i sprawnosc chromosomu
	for (int i = 0; i < chrSize; i++)
	{
		// uzyskaj zawartosc chromosomu
		unsigned char value = chr1->GetChromosome(i);

		// zapisz zawartosc chromosomu do chromosomu docelowego
		chr2->SetChromosome(i, value);
	}

	// ustaw sprawnosc
	double fitness = chr1->GetFitness();
	chr2->SetFitness(fitness);
}
