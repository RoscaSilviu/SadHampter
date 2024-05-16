#pragma once
#include <array>
class Chromosome
{
public:
	static constexpr int kDimention = 10;
	
public:
	Chromosome();

	void Mutation();
	void Fitness();

private:
	std::array<bool, kDimention> m_x;
	std::array<bool, kDimention> m_y;
	int fitness;
};

