

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "main.h"

#define INF INT_MAX

int main(int argc, char const *argv[])
{
	ACOGraph testGraph;
	testGraph.nbNodes = 7;
	allocateAndInitializeACOGraphContents(&testGraph);

    uint start_pos = 1;
    uint target_pos = 5;

	uint tempNodes[7][7] = {
	 {INF,1,  1,  1,  INF,INF,INF},
	 {1,  INF,INF,INF,INF,INF,1  },
	 {1,  INF,INF,INF,INF,1,  INF},
	 {1,  INF,INF,INF,1,INF,  INF},
	 {INF,INF,INF,1,  INF,1,  INF},
	 {INF,INF,1,  INF,1,INF,  1  },
	 {INF,1,  INF,INF,INF,1,  INF}
	};

	for (int i = 0; i < testGraph.nbNodes; ++i)
	{
		memcpy(testGraph.nodes[i], tempNodes[i], sizeof(uint)*testGraph.nbNodes);
	}



	return 0;
}

void allocateAndInitializeACOGraphContents(ACOGraph* g)
/* Remember to assign a value to g.nbNodes */
{
	g->nodes = malloc(sizeof(int*) * g->nbNodes);
	g->pheromone = malloc(sizeof(int*) * g->nbNodes);


	for (int i = 0; i < g->nbNodes; ++i)
	{
		g->nodes[i] = malloc(sizeof(int) * g->nbNodes);
		g->pheromone[i] = malloc(sizeof(int) * g->nbNodes);

		for (int j = 0; j < g->nbNodes; ++j)
		{
			g->nodes[i][j] = INF;
			g->pheromone[i][j] = 0;

		}
	}


}

void evaporatePheromones(ACOGraph* g)
{
	uint pRate = 0.5;
	for (int i = 0; i < g->nbNodes; ++i) {
		for (int j = 0; j < g->nbNodes; ++j) {
			g->pheromone[i][j] = (1 - pRate) * g->pheromone[i][j];
		}
	}	
}