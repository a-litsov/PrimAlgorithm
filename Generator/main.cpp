#include <string>
#include <fstream>
#include <direct.h>

#include "RCGGenerator.h"

int testsCount = 10;

int main(int argc, char** argv)
{
	_mkdir("tests");
	int n, **g;
	for (int i = 1; i <= testsCount; i++) {
		std::ofstream outfile("tests/" + std::to_string(i) + ".in", std::ios::binary | std::ios::out);

		n = i * 100;
		g = RCGGenerator::getAdjacencyMatrix(n);
		outfile.write((char*)&n, sizeof(int));
		for (int j = 0; j < n; j++)
			outfile.write((char*)g[j], n * sizeof(int));

		outfile.close();

		for (int j = 0; j < n; j++)
			delete[] g[j];
		delete[] g;
	}
	return 0;
}