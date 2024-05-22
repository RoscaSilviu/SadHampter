#pragma once
#include <vector>
#include <string>

class Chromosome
{
public:
	static constexpr int kDimension{ 10 };
	static constexpr double kMutationProbability { 0.001 };

public:
	Chromosome() = default;
	Chromosome(const double xLeftBoundary, const double xRightBoundary, 
		const double yLeftBoundary, const double yRightBoundary);

	void Mutation();
	std::vector<bool> GetX() const;
	std::vector<bool> GetY() const;
	double GetXPhenotype() const;
	double GetYPhenotype() const;
	double GetFitness() const;

	std::string GetChromosome();

	void SetX(const std::vector<bool>& x);
	void SetY(const std::vector<bool>& y);

public:
	bool operator<(const Chromosome& other) const;
	bool operator==(const Chromosome& other) const;

private:
	void Fitness();
	double DecodeGene(bool isX) const;
	static int GetV(const std::vector<bool>& gene);
private:

	std::vector<bool> m_x;
	std::vector<bool> m_y;
	double m_fitness;

	double m_xLeftBoundary;
	double m_xRightBoundary;
	double m_yLeftBoundary;
	double m_yRightBoundary;
};

