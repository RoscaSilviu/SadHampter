#pragma once
#include <array>
class Chromosome
{
public:
	static constexpr int kDimension{ 10 };
	static constexpr double kMutationProbability { 0.001 };

public:
	Chromosome(const double leftBoundary, const double rightBoundary);
	void Mutation();
	std::array<bool, kDimension> GetX() const;
	std::array<bool, kDimension> GetY() const;
	double GetXPhenotype() const;
	double GetYPhenotype() const;
	double GetFitness() const;

public:
	bool operator<(const Chromosome& other) const;

private:
	void Fitness();
	double DecodeGene(const std::array<bool, kDimension>& gene) const;
	static int GetV(const std::array<bool, kDimension>& gene);
private:
	std::array<bool, kDimension> m_x;
	std::array<bool, kDimension> m_y;
	double m_fitness;
	double m_leftBoundary;
	double m_rightBoundary;
};

