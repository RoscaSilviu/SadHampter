#include "Population.h"
#include <fstream>

int main()
{
	std::ofstream out("output.txt");

	Population population(-5, 3, 2, 10);
	for (int i = 0; i < 20; ++i)
	{
		population.Selection();
		population.Repopulate();
		
		out << "#Generation " << i << "\n";
		out << population;
		out << "\n";
	}
	// print biggest result;
	return 0;
}