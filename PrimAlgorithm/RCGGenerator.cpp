#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <map>
#include <set>

#include "constants.h"
#include "RCGGenerator.h"

int RCGGenerator::getStart(int end, int** g, int n)
{
	for (int i = 0; i < n; i++)
	if (g[i][end] != INF)
		return i;
	return INF;
}

int RCGGenerator::getEnd(int start, int** g, int n)
{
	for (int i = 0; i < n; i++)
	if (g[start][i] != INF)
		return i;
	return INF;
}

int RCGGenerator::fillOneVertex(int &start, int &end, int** g, int n)
{
	srand(int(time(0)));
	start = rand() % n;
	end = rand() % n;
	while (end == start)
		end = rand() % n;
	while (g[start][end] != INF) {
		start = rand() % n;
		end = rand() % n;
		while (end == start)
			end = rand() % n;
	}
	return g[end][start] = g[start][end] = rand() % 200;
}

int** RCGGenerator::initializeGraphMatrix(int n)
{
	int** g = new int*[n];
	for (int i = 0; i < n; i++) {
		g[i] = new int[n];
		for (int j = 0; j < n; j++)
			g[i][j] = INF;
	}
	return g;
}

// n >= 4
int** RCGGenerator::generateConnectedGraph(int n)
{
	int** g = initializeGraphMatrix(n);

	std::set<std::set<int>*> groupSet;

	// Generates n*(n-1)/4 vertices, fills groups
	for (int i = 0; i < (n - 1)*(n - 2) / 2 + 1; i++) {
		int start, end, value;
		value = fillOneVertex(start, end, g, n);
		std::set<int> *foundStart = 0, *foundEnd = 0;
		bool isStartFound = false, isEndFound = false;
		for (auto const& item : groupSet) {
			auto search = item->find(start);
			if (search != item->end()) {
				foundStart = item;
				isStartFound = true;
			}
			search = item->find(end);
			if (search != item->end()) {
				foundEnd = item;
				isEndFound = true;
			}
		}
		if (foundStart != 0 && foundEnd != 0) {
			foundStart->insert(foundEnd->begin(), foundEnd->end());
			groupSet.erase(foundEnd);
		}
		else {
			if (isStartFound) {
				foundStart->insert(end);
			}
			else {
				if (isEndFound) {
					foundEnd->insert(start);
				}
				else {
					std::set<int>* newSet = new std::set<int>();
					newSet->insert(start);
					newSet->insert(end);
					groupSet.insert(newSet);
				}
			}
		}
	}

	// Makes connections between groups
	std::set<std::set<int>*>::iterator it;
	for (it = groupSet.begin(); it != groupSet.end(); it++) {
		std::set<std::set<int>*>::iterator next_it = next(it);
		if (next_it != groupSet.end()) {
			int start = *((*it)->begin());
			int end = *((*next_it)->begin());
			fillOneVertex(start, end, g, n);
		}
	}


	return g;
}

void RCGGenerator::showGraph(int** g, int n)
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