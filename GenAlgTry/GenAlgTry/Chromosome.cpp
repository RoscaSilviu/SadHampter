#include "Chromosome.h"
#include <cmath>
#include <random>

Chromosome::Chromosome(const double XleftBoundary, const double XrightBoundary,
	const double YleftBoundary, const double yrightBoundary):
	m_XleftBoundary(XleftBoundary)
	, m_XrightBoundary(XrightBoundary)
	, m_YleftBoundary(YleftBoundary)
	, m_YrightBoundary(yrightBoundary)
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

void Chromosome::Fitness()
{
	const auto x = GetXPhenotype();
	const auto y = GetYPhenotype();
	const double result = 3+abs(log(sin(x) * 5 + 3)+tan(y));

	m_fitness = result;
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
	return DecodeGene(m_x, true);
}

double Chromosome::GetYPhenotype() const
{
	return DecodeGene(m_y, false);
}

double Chromosome::GetFitness() const
{ return m_fitness; }

bool Chromosome::operator<(const Chromosome& other) const
{
	return m_fitness < other.m_fitness;
}

double Chromosome::DecodeGene(const std::array<bool, kDimension>& gene, bool isX) const
{
	const auto v = GetV(gene);
	if(isX)
	{
		return m_XleftBoundary + v * (m_XrightBoundary - m_XleftBoundary) / (pow(2, kDimension) - 1);
	}
	return m_YleftBoundary + v * (m_YrightBoundary - m_YleftBoundary) / (pow(2, kDimension) - 1);
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

