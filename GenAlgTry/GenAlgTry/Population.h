#pragma once
#include "Chromosome.h"

class Population
{
public:
	Population();
	void Selection();
	void Crossover();

private:
	static constexpr int kDimension = 100;

	std::array<Chromosome, kDimension> m_population;

	int m_startX;
	int m_startY;
	int m_endX;
	int m_endY;
};

