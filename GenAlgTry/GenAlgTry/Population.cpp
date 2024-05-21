#include "Population.h"
#include <random>

Population::Population()
{
	for (int i = 0; i < kPopulationDimension; ++i)
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
	for (int i = 0; i < kPopulationDimension; ++i)
	{
		m_population[i] = Chromosome(m_startX, m_endX, m_startY, m_endY);
	}

	Selection();
}

void Population::Selection()
{
	CalculateCumulativeProbability();
	for (int i = 0; i < kPopulationDimension / 2; ++i)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(0, 1);
		double random = dis(gen);
		double random2 = dis(gen);
		double randValue = dis(gen);
		if (randValue < kPC)
		{
			auto individuals = std::make_pair(GetChromosomeByProbability(random), GetChromosomeByProbability(random2));
			m_selected.insert(individuals);
			
		}
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
	for (int i = 0; i < kPopulationDimension; ++i)
	{
		m_relativeFitness[i] = cumulativeProbability + m_population[i].GetFitness() / totalFitness;
		m_cumulativeProbability.insert(std::make_pair(m_population[i], m_relativeFitness[i]));
		cumulativeProbability += m_relativeFitness[i];
	}
}

std::set<std::pair<Chromosome, Chromosome>> Population::Crossover()
{
	std::set<std::pair<Chromosome, Chromosome>> offsprings;

	for (const auto& parents : m_selected)
	{
		std::vector<bool> firstParentGene, secondParentGene; // combine x and y genes into a single array
		std::copy(parents.first.GetX().begin(), parents.first.GetX().end(), firstParentGene.begin());
		std::copy(parents.first.GetY().begin(), parents.first.GetY().end(), firstParentGene.begin() + Chromosome::kDimension);
		std::copy(parents.second.GetX().begin(), parents.second.GetX().end(), secondParentGene.begin());
		std::copy(parents.second.GetY().begin(), parents.second.GetY().end(), secondParentGene.begin() + Chromosome::kDimension);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(1, parents.first.GetX().size() - 1); // doesn't choose the first or last position of the gene
		int randIndex = dis(gen);

		std::vector<bool> firstOffspringGene, secondOffspringGene;

		for (int i = 0; i < Chromosome::kDimension * 2; i++)
		{
			if (i < randIndex)
			{
				firstOffspringGene[i] = firstParentGene[i];
				secondOffspringGene[i] = secondParentGene[i];
			}
			else
			{
				firstOffspringGene[i] = secondParentGene[i];
				secondOffspringGene[i] = firstParentGene[i];
			}
		}

		Chromosome firstOffspring, secondOffSpring;
		std::copy(firstOffspringGene.begin(), firstOffspringGene.begin() + Chromosome::kDimension, firstOffspring.GetX().begin());
		std::copy(firstOffspringGene.begin() + Chromosome::kDimension, firstOffspringGene.end(), firstOffspring.GetY().begin());
		std::copy(secondOffspringGene.begin(), secondOffspringGene.begin() + Chromosome::kDimension, secondOffSpring.GetX().begin());
		std::copy(secondOffspringGene.begin() + Chromosome::kDimension, secondOffspringGene.end(), secondOffSpring.GetY().begin());

		offsprings.insert(std::make_pair(firstOffspring, secondOffSpring));		
	}
	return offsprings;
}
