#ifndef Prim_RCGGenerator
#define Prim_RCGGenerator

// Random Connected Graphs Generator
class RCGGenerator
{
public:
	static int getStart(int end, int** g, int n);
	static int getEnd(int start, int** g, int n);
	static int** initializeGraphMatrix(int n);
	static int** generateConnectedGraph(int n);
	static void showGraph(int** g, int n);
private:
	static int getRandomWeight();
	static int getRandomVertex(int n);
};

#endif