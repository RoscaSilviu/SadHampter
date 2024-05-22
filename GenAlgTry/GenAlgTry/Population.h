#pragma once
#include <set>

#include "Chromosome.h"

class Population
{
public:
	static constexpr int kPopulationDimension = 100;
	static constexpr double kProbabilityChance = 0.613;
public:

	Population(const double startX, const double endX, const double startY, const double endY);

	void Selection();
	std::vector<std::pair<Chromosome, Chromosome>> Crossover(); // returns offsprings
	void DeleteTheWeaklings(size_t size);
	void Repopulate();

	friend std::ostream& operator<<(std::ostream& os, const Population& p);


private:
	//binary search on set
	Chromosome GetChromosomeByProbability(double probability) const;
	void CalculateCumulativeProbability();
	void EraseIndividual(const Chromosome& individual);
private:
	double m_startX;
	double m_startY;
	double m_endX;
	double m_endY;
private:
	std::vector<Chromosome> m_population;
	std::vector<std::pair<Chromosome, double>> m_cumulativeProbability;
	std::vector<std::pair<Chromosome, Chromosome>> m_selected;

	
};

