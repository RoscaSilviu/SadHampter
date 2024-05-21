#pragma once
#include <vector>

class Chromosome
{
public:
	static constexpr int kDimension{ 10 };
	static constexpr double kMutationProbability { 0.001 };

public:
	Chromosome() = default;
	Chromosome(const double XleftBoundary, const double XrightBoundary, 
		const double YleftBoundary, const double yrightBoundary);

	void Mutation();
	std::vector<bool> GetX() const;
	std::vector<bool> GetY() const;
	double GetXPhenotype() const;
	double GetYPhenotype() const;
	double GetFitness() const;

	void SetX(const std::vector<bool>& x);
	void SetY(const std::vector<bool>& y);

public:
	bool operator<(const Chromosome& other) const;
	bool operator==(const Chromosome& other) const;

private:
	void Fitness();
	double DecodeGene(const std::vector<bool>& gene, bool isX) const;
	static int GetV(const std::vector<bool>& gene);
private:

	std::vector<bool> m_x;
	std::vector<bool> m_y;
	double m_fitness;

	double m_XleftBoundary;
	double m_XrightBoundary;
	double m_YleftBoundary;
	double m_YrightBoundary;
};

