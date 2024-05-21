#pragma once
#include <set>

#include "Chromosome.h"

class Population
{
public:
	static constexpr int kPopulationDimension = 100;
	static constexpr double kPC = 0.613;
public:
	Population();
	Population(const int startX, const int startY, const int endX, const int endY);

	void Selection();
	std::set<std::pair<Chromosome, Chromosome>> Crossover(); // returns offsprings
	void Repopulate();

private:
	//binary search on set
	Chromosome GetChromosomeByProbability(double probability) const;
	void CalculateCumulativeProbability();

	//std::array<Chromosome, kDimension> m_population;
	std::array<Chromosome, kPopulationDimension> m_population;
	std::array<double, kPopulationDimension> m_relativeFitness;
	std::set<std::pair<Chromosome, double>> m_cumulativeProbability;
	std::set<std::pair<Chromosome, Chromosome>> m_selected;
	

	int m_startX;
	int m_startY;
	int m_endX;
	int m_endY;
};

