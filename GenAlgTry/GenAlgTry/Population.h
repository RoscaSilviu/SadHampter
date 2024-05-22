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
	std::vector<std::pair<Chromosome, Chromosome>> Crossover(); // returns offsprings
	void Repopulate();
	void ShowPopulation() const;

	//friend std::ostream& operator<<(std::ostream& os, const Population& p);
	friend std::ostream& operator<<(std::ostream& os, const Population& p);


private:
	//binary search on set
	Chromosome GetChromosomeByProbability(double probability) const;
	void CalculateCumulativeProbability();
	void EraseIndividual(const Chromosome& individual);
	std::vector<bool> CombineGenes(const Chromosome& ch);
	std::pair< std::vector<bool>,std::vector<bool>> SplitGene(const std::vector<bool>& gene);

	std::vector<Chromosome> m_population;
	std::vector<double> m_relativeFitness;
	std::vector<std::pair<Chromosome, double>> m_cumulativeProbability;
	std::vector<Chromosome> m_selectedPopulation;
	std::vector<std::pair<Chromosome, Chromosome>> m_selected;

	int m_startX;
	int m_startY;
	int m_endX;
	int m_endY;
};

