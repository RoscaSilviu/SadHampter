#include "Chromosome.h"
#include <cmath>
#include <iostream>
#include <random>

Chromosome::Chromosome(const double xLeftBoundary, const double xRightBoundary,
	const double yLeftBoundary, const double yRightBoundary) :
	m_xLeftBoundary{ xLeftBoundary }
	, m_xRightBoundary{ xRightBoundary }
	, m_yLeftBoundary{ yLeftBoundary }
	, m_yRightBoundary{ yRightBoundary }
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);
	m_x = std::vector<bool>(kDimension);	
	m_y = std::vector<bool>(kDimension);

	for(int index =0; index < kDimension; ++index)
	{
		m_x[index] = dis(gen) > 0.5;
		m_y[index] = dis(gen) > 0.5;
	}

	Fitness();
}

Chromosome::Chromosome(const double xLeftBoundary, const double xRightBoundary, const double yLeftBoundary,
	const double yRightBoundary, const std::vector<bool>& genes):
	m_xLeftBoundary{ xLeftBoundary }
	, m_xRightBoundary{ xRightBoundary }
	, m_yLeftBoundary{ yLeftBoundary }
	, m_yRightBoundary{ yRightBoundary }
{
	const auto half = genes.size() / 2;
	m_x = std::vector<bool>(genes.begin(), genes.begin() + half);
	m_y = std::vector<bool>(genes.begin() + half, genes.end());
	Fitness();
}

void Chromosome::Mutation()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0, 1);

	for (int index = 0; index < kDimension; ++index)
	{
		if (dis(gen) < kMutationProbability)
		{
			m_x[index] = !m_x[index];
		}
		if (dis(gen) < kMutationProbability)
		{
			m_y[index] = !m_y[index];
		}
	}
}

void Chromosome::Fitness()
{
	const auto x = GetXPhenotype();
	const auto y = GetYPhenotype();

	const double intermediateLogArg = sin(x) * 5 + 3;
	const double intermediateTan = std::tan(y);

	double result{ 0.0 };// a default value must be assigned to result

	//if the intermediateLogArg and intermediateTan are good we assign the result
	if (!(intermediateLogArg <= 0 || std::isinf(intermediateTan) || std::isnan(intermediateTan))) {
		result = 3 + abs(log(intermediateLogArg) + intermediateTan);
	}
	m_fitness = result;
}

std::vector<bool> Chromosome::GetX() const
{
	return m_x;
}

std::vector<bool> Chromosome::GetY() const
{
	return m_y;
}

double Chromosome::GetXPhenotype() const
{
	return DecodeGene(true);
}

double Chromosome::GetYPhenotype() const
{
	return DecodeGene(false);
}

double Chromosome::GetFitness() const
{
	return m_fitness;
}

std::vector<bool> Chromosome::GetGene() const
{
	std::vector<bool> result;
	result.insert(result.end(), m_x.begin(), m_x.end());
	result.insert(result.end(), m_y.begin(), m_y.end());
	return result;
}

std::string Chromosome::GetChromosome() 
{
	std::string result;
	for (const auto& gene : m_x)
	{
		result += gene ? "1" : "0";
	}
	for (const auto gene : m_y)
	{
		result += gene ? "1" : "0";
	}
	return result;
}

void Chromosome::SetX(const std::vector<bool>& x)
{
	m_x = x;
}

void Chromosome::SetY(const std::vector<bool>& y)
{
	m_y = y;
}

bool Chromosome::operator<(const Chromosome& other) const
{
	return m_fitness < other.m_fitness;
}

bool Chromosome::operator==(const Chromosome& other) const
{
	return this->m_x == other.m_x &&
		this->m_y == other.m_y;
}

double Chromosome::DecodeGene(const bool isX) const
{
	if (isX)
	{
		const auto v = GetV(m_x);
		return m_xLeftBoundary + v * (m_xRightBoundary - m_xLeftBoundary) / (pow(2, kDimension) - 1);
	}

	const auto v = GetV(m_y);
	return m_yLeftBoundary + v * (m_yRightBoundary - m_yLeftBoundary) / (pow(2, kDimension) - 1);
}

int Chromosome::GetV(const std::vector<bool>& gene)
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

