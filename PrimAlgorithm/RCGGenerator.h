#ifndef Prim_RCGGenerator
#define Prim_RCGGenerator

// Random Connected Graphs Generator
class RCGGenerator
{
public:
	static int getStart(int end, int** g, int n);
	static int getEnd(int start, int** g, int n);
	static int fillOneVertex(int &start, int &end, int** g, int n);
	static int** initializeGraphMatrix(int n);
	static int** generateConnectedGraph(int n);
	static void showGraph(int** g, int n);
};

#endif