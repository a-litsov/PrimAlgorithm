#include <omp.h>
#include <fstream>

int PrimAlgorithm(int n, int** g);

int main(int argc, char * argv[])
{
	int num_threads = 1;
	if (argc > 1)
		num_threads = atoi(argv[1]);

	std::ifstream infile("graph.in", std::ios::binary | std::ios::in);
	std::ofstream outfile("graph.out", std::ios::binary | std::ios::out);

	/* memory allocation */
	int n;
	int **g = new int*[n];
	for (int i = 0; i < n; i++)
		g[i] = new int[n];

	/* reading */
	infile.read((char*)&n, sizeof(int));
	for (int i = 0; i < n; i++)
	{
		infile.read((char *)g[i], n * sizeof(int));
	}

	/* executing */
	omp_set_num_threads(num_threads);

	double time = omp_get_wtime();
	int minWeight =  PrimAlgorithm(n, g);
	time = omp_get_wtime() - time;

	/* writing */
	outfile.write((char*)&time, sizeof(double));
	outfile.write((char*)&minWeight, sizeof(int));

	outfile.close();
	infile.close();
	return 0;
}

#define main main_lumos_