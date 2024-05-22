#pragma once
#include <set>

#include "Chromosome.h"

class Population
{
public:
	static constexpr int kPopulationDimension = 100;
	static constexpr double kProbabilityChance = 0.613;
public:
	Population();
	Population(const double startX, const double startY, const double endX, const double endY);

	void Selection();
	std::vector<std::pair<Chromosome, Chromosome>> Crossover(); // returns offsprings
	void Repopulate();
	void ShowPopulation() const;

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
	std::vector<double> m_relativeFitness;
	std::vector<std::pair<Chromosome, double>> m_cumulativeProbability;
	std::vector<Chromosome> m_selectedPopulation;
	std::vector<std::pair<Chromosome, Chromosome>> m_selected;

	
};

