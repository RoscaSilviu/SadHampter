#include "Population.h"
#include <random>
#include <iostream>

Population::Population()
{
	for (int i = 0; i < kPopulationDimension; ++i)
	{
		m_population.emplace_back(m_startX, m_endX, m_startY, m_endY);
	}

	Selection();
}

Population::Population(const double startX, const double startY, const double endX, const double endY) :
	m_startX(startX)
	, m_startY(startY)
	, m_endX(endX)
	, m_endY(endY)
{
	m_relativeFitness = std::vector<double>(kPopulationDimension);

	for (int i = 0; i < kPopulationDimension; ++i)
	{
		m_population.emplace_back(m_startX, m_endX, m_startY, m_endY);
	}
	//Selection();
}

void Population::Selection()
{
	m_selectedPopulation.clear();
	m_selected.clear();
	CalculateCumulativeProbability();
	for (int i = 0; i < kPopulationDimension / 2; ++i)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(0, 1);
		const double random = dis(gen);
		const double random2 = dis(gen);

		if (dis(gen) < kProbabilityChance)
		{
			auto firstIndividual = GetChromosomeByProbability(random);
			auto secondIndividual = GetChromosomeByProbability(random2);
			
			if (firstIndividual.GetX().size() != Chromosome::kDimension || secondIndividual.GetX().size() != Chromosome::kDimension)
			{
				//throw std::runtime_error("The size of the gene is not equal to the dimension of the chromosome");
			}
			
			m_selected.emplace_back(firstIndividual, secondIndividual);
			m_selectedPopulation.emplace_back(firstIndividual);
			m_selectedPopulation.emplace_back(secondIndividual);

			EraseIndividual(firstIndividual);
			EraseIndividual(secondIndividual);
		}
	}
}

Chromosome Population::GetChromosomeByProbability(const double probability) const
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
		m_cumulativeProbability.emplace_back(m_population[i], m_relativeFitness[i]);
		cumulativeProbability += m_relativeFitness[i];
	}
}

void Population::EraseIndividual(const Chromosome& individual)
{
	const auto it = std::ranges::find(m_population, individual);
	if (it != m_population.end())
	{
		m_population.erase(it);
	}
}


std::vector<std::pair<Chromosome, Chromosome>> Population::Crossover()
{
	std::vector<std::pair<Chromosome, Chromosome>> offsprings;

	for (const auto& [firstParent, secondParent] : m_selected)
	{
		std::vector<bool> firstParentGene = firstParent.GetGene();
		std::vector<bool> secondParentGene = secondParent.GetGene();

		std::random_device rd;
		std::mt19937 gen(rd());
		if (firstParent.GetX().size() != Chromosome::kDimension)
		{
			throw std::runtime_error("The size of the gene is not equal to the dimension of the chromosome");
		}

		std::uniform_int_distribution<int> dis(1, Chromosome::kDimension - 1); // doesn't choose the first or last position of the gene
		int randIndex = dis(gen);

		std::vector<bool> firstOffspringGene, secondOffspringGene;
		firstOffspringGene.resize(Chromosome::kDimension * 2);
		secondOffspringGene.resize(Chromosome::kDimension * 2);

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

		Chromosome firstOffspring = { m_startX, m_endX, m_startY, m_endY ,firstOffspringGene };
		Chromosome secondOffSpring = { m_startX, m_endX, m_startY, m_endY ,secondOffspringGene };

		offsprings.emplace_back(firstOffspring, secondOffSpring);		
	}
	return offsprings;
}

void Population::Repopulate()
{
	const auto offsprings = Crossover();	
	for (auto offspring : offsprings)
	{
		offspring.first.Mutation();
		offspring.second.Mutation();
		m_population.push_back(offspring.first);
		m_population.push_back(offspring.second);
	}
}

void Population::ShowPopulation() const
{/*
	for (const auto& chromosome : m_population)
	{
		std::cout << chromosome.GetChromosome() << "X: " << chromosome.GetXPhenotype() << " Y: " << chromosome.GetYPhenotype() << " Fitness: " << chromosome.GetFitness() << std::endl;
	}*/
}

std::ostream& operator<<(std::ostream& os, const Population& p) {
	os << "Population Size: " << p.m_population.size() << "\n";
	os << "Population Coordinates: Start (" << p.m_startX << ", " << p.m_startY << ") End (" << p.m_endX << ", " << p.m_endY << ")\n";
	os << "Chromosomes in Population:\n";
	for (auto chromosome : p.m_population) {
		os << chromosome.GetChromosome()<<" "<<chromosome.GetFitness() << "\n";
	}
	return os;
}