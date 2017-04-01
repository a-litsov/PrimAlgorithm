#include <vector>
#include <assert.h>
#include <omp.h>

#include "constants.h"

int PrimAlgorithm(int n, int** g)
{
    int res = 0;
    std::vector<bool> used (n);
    std::vector<int> min_e (n, INF); // min_e[i] - вес наименьшего допустимого ребра из вершины i
    std::vector<int> sel_e (n, -1); // sel_e[i] - конец этого наименьшего ребра
    min_e[0] = 0;
    for (int i=0; i<n; ++i)
	{
        int v = -1;
		for (int j = 0; j < n; ++j)
		{
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
			{
				v = j;
			}
		}
		assert(min_e[v] != INF);
        
        used[v] = true;
        if (sel_e[v] != -1)
            res += g[v][sel_e[v]];
        
#pragma omp parallel for
        for (int to=0; to<n; ++to)
            if (g[v][to] < min_e[to]) {
                min_e[to] = g[v][to];
                sel_e[to] = v;
                
            }
    }
    return res;
}
