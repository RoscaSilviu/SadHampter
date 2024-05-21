#include "Population.h"

#include <algorithm>
#include <random>

Population::Population()
{
	//initialize the population
	for (auto& chromosome : m_population)
	{
		chromosome = Chromosome(-10, 10);
	}
	Selection();
}

void Population::Selection()
{
	double totalFitness = 0;
	double cumulativeProbability = 0;
	for (const auto& chromosome : m_population)
	{
		totalFitness += chromosome.GetFitness();
	}
	std::array<double, kDimension - kUnselected> relativeFitness;
	for (int i = 0; i < kDimension - kUnselected; ++i)
	{
		relativeFitness[i] = cumulativeProbability + m_population[i].GetFitness() / totalFitness;
		cumulativeProbability += relativeFitness[i];
	}

	Chromosome parent1(m_startX, m_endX), parent2(m_startX, m_endX);

	for (int i = 0; i < kDimension - kUnselected; ++i)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(0, 1);
		double random = dis(gen);
		for (int j = 0; j < kDimension - kUnselected; ++j)
		{
			if (random < relativeFitness[j])
			{
				m_selected[i].first = m_population[j];
				break;
			}
		}
		random = dis(gen);
		for (int j = 0; j < kDimension - kUnselected; ++j)
		{
			if (random < relativeFitness[j])
			{
				m_selected[i].second = m_population[j];
				break;
			}
		}
	}
}
