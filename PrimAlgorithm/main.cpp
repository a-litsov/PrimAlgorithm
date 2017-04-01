#include <iostream>
#include <omp.h>

#include "RCGGenerator.h"
#include "sol.h"

int main(int argc, char** argv) {
	int n = 4;
	int** g = RCGGenerator::generateConnectedGraph(n);

	RCGGenerator::showGraph(g, n);

	int minWeight = PrimAlgorithm(n, g);
	std::cout << "Min weight is " << minWeight << "\n";
	for (int i = 0; i < n; i++)
		delete[] g[i];
	delete[] g;
	return 0;
}