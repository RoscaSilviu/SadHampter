#include "Population.h"
#include <random>

Population::Population()
{
	for (int i = 0; i < kDimension; ++i)
	{
		m_population[i] = Chromosome(m_startX, m_endX, m_startY, m_endY);
	}

	Selection();
}

Population::Population(const int startX, const int startY, const int endX, const int endY):
	m_startX(startX)
	, m_startY(startY)
	, m_endX(endX)
	, m_endY(endY)
{
	for (int i = 0; i < kDimension; ++i)
	{
		m_population[i] = Chromosome(m_startX, m_endX, m_startY, m_endY);
	}

	Selection();
}

void Population::Selection()
{
	CalculateCumulativeProbability();
	for (int i = 0; i < kDimension; ++i)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(0, 1);
		double random = dis(gen);
		double random2 = dis(gen);
		m_selected.insert(std::make_pair(GetChromosomeByProbability(random), GetChromosomeByProbability(random2)));
	}
}

Chromosome Population::GetChromosomeByProbability(double probability) const
{
	for (const auto& chromosome : m_cumulativeProbability)
	{
		if (chromosome.second >= probability)
		{
			 return chromosome.first;
		}
	}
}

void Population::CalculateCumulativeProbability()
{
	double totalFitness = 0;
	double cumulativeProbability = 0;
	for (const auto& chromosome : m_population)
	{
		totalFitness += chromosome.GetFitness();
	}

	m_cumulativeProbability.clear();
	for (int i = 0; i < kDimension; ++i)
	{
		m_relativeFitness[i] = cumulativeProbability + m_population[i].GetFitness() / totalFitness;
		m_cumulativeProbability.insert(std::make_pair(m_population[i], m_relativeFitness[i]));
		cumulativeProbability += m_relativeFitness[i];
	}
}
