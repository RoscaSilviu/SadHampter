#include "Chromosome.h"
#include <cmath>
#include <random>


Chromosome::Chromosome(const double leftBoundary, const double rightBoundary):
	m_leftBoundary(leftBoundary)
	, m_rightBoundary(rightBoundary)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0, 1);

	for (auto& gene : m_x)
	{
		gene = dis(gen) > 0.5;
	}
	for (auto& gene : m_y)
	{
		gene = dis(gen) > 0.5;
	}
	Fitness();
}

void Chromosome::Mutation()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0, 1);

	for(auto& gene : m_x)
	{
		if(dis(gen) < kMutationProbability)
		{
			gene = !gene;
		}
	}
	for(auto& gene : m_y)
	{
		if(dis(gen) < kMutationProbability)
		{
			gene = !gene;
		}
	}
}

double Chromosome::Fitness()
{
	const auto x = DecodeGene(m_x);
	const auto y = DecodeGene(m_y);
	const double result = 3+abs(log(sin(x) * 5 + 3)+tan(y));

	m_fitness = result;
	return result;
}

std::array<bool, Chromosome::kDimension> Chromosome::GetX() const
{
	return m_x;
}

std::array<bool, Chromosome::kDimension> Chromosome::GetY() const
{
	return m_y;
}

double Chromosome::GetXPhenotype() const
{
	return DecodeGene(m_x);
}

double Chromosome::GetYPhenotype() const
{
	return DecodeGene(m_y);
}

double Chromosome::DecodeGene(const std::array<bool, kDimension>& gene) const
{
	const auto v = GetV(gene);
	return m_leftBoundary + v * (m_rightBoundary-m_leftBoundary) / (pow(2, kDimension) - 1);
}

int Chromosome::GetV(const std::array<bool, kDimension>& gene)
{
	int result = 0.0;
	int index = 0;
	for (auto i = kDimension - 1; i >= 0; --i)
	{
		if (gene[i])
		{
			result += pow(2, index);
		}
		++index;
	}
	return result;
}

