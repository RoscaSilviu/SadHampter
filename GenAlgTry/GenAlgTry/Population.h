#pragma once
#include "Chromosome.h"

class Population
{
public:
	static constexpr int kDimension = 10;
	static constexpr int kUnselected = 3;
public:
	Population();
	void Selection();
	void Crossover();
	void Repopulate();

private:

	std::array<Chromosome, kDimension> m_population;
	std::array<std::pair<Chromosome, Chromosome>, kDimension - kUnselected> m_selected;

	int m_startX;
	int m_startY;
	int m_endX;
	int m_endY;
};

