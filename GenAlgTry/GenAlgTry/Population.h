#pragma once
#include "Chromosome.h"

class Population
{
public:
	static constexpr int kDimension = 100;
public:
	Population();
	void Selection();
	void Crossover();

private:

	std::array<Chromosome, kDimension> m_population;

	int m_startX;
	int m_startY;
	int m_endX;
	int m_endY;
};

