#ifndef Prim_RCGGenerator
#define Prim_RCGGenerator

// Random Connected Graphs Generator
class RCGGenerator
{
public:
	static int** initializeGraphMatrix(int n);
	static int** getAdjacencyMatrix(int n);
	static void showAdjacencyMatrix(int** g, int n);
private:
	static int getRandomWeight();
	static int getRandomVertex(int n);
};

#endif