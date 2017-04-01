#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <unordered_map>

#include "constants.h"
#include "RCGGenerator.h"

int RCGGenerator::getRandomWeight()
{
	return rand() % MAX_WEIGHT;
}
int RCGGenerator::getRandomVertex(int n)
{
	return rand() % n;
}

int** RCGGenerator::initializeGraphMatrix(int n)
{
	int** g = new int*[n];
	for (int i = 0; i < n; i++)
	{
		g[i] = new int[n];
		for (int j = 0; j < n; j++)
			g[i][j] = INF;
	}
	return g;
}

int** RCGGenerator::getAdjacencyMatrix(int n)
{
	srand(int(time(0)));
	int** g = initializeGraphMatrix(n);

	int maxEdgesCount = n*(n - 1) / 2;
	int m = (rand() % (maxEdgesCount - (n - 1) + 1)) + n - 1;
	int *prevArray = new int[n];
	std::unordered_map<int, bool> prevMap;

	
	prevArray[0] = getRandomVertex(n);
	prevMap[prevArray[0]] = true;
	
	int start, end, value;
	// Generates 1 edge for each vertex
	for (int i = 1; i < n; i++) {
		start = prevArray[rand() % i], end = getRandomVertex(n), value = getRandomWeight();
		while (prevMap[end] == true)
			end = getRandomVertex(n);

		g[start][end] = value;
		g[end][start] = value;
		prevArray[i] = end;
		prevMap[end] = true;
	}

	int remainingEdges = (m == n-1) ? 0 : rand() % (m - n + 1);
	std::cout << remainingEdges << "\n" << m << "\n";
	for (int i = 0; i < remainingEdges; i++)
	{
		value = getRandomWeight();
		while (g[start][end] != INF)
		{
			start = getRandomVertex(n);
			end = getRandomVertex(n);
		}
		g[start][end] = value;
		g[end][start] = value;
	}
	delete[] prevArray;
	return g;
}

void RCGGenerator::showAdjacencyMatrix(int** g, int n)
{
	std::cout << "Graph is:\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << std::setw(10);
			std::cout << g[i][j] << " ";
		}
		std::cout << "\n";
	}
}