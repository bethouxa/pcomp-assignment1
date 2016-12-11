#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "main.h"

#define INF INT_MAX

#define NB_SIMUL_ANTS 1

void populateTestData(ACOGraph* g);

int main(int argc, char const *argv[])
{
	ACOGraph* g = calloc(1,sizeof(ACOGraph));
	Ant* ants = calloc(NB_SIMUL_ANTS, sizeof(Ant));

	initAnts(ants, NB_SIMUL_ANTS);
	allocateAndInitializeACOGraphContents(g, 5);
	populateTestData(g);

	uint tickCount = 0;

	while(tickCount < 100000)
	{
		for(uint antIndex=0; antIndex<NB_SIMUL_ANTS; ++antIndex)
		{
			move(&ants[antIndex], g);
		}
		evaporatePheromones(g);
		tickCount++;
	}
	printStrongestPheromoneTrail(g,0);

	return 0;
}


void populateTestData(ACOGraph* g)
{
	addEdge(g, 0, 1, 1);
	addEdge(g, 0, 3, 1);
	addEdge(g, 1, 2, 1);
	addEdge(g, 1, 3, 1);
	addEdge(g, 3, 2, 1);
	addEdge(g, 3, 4, 1);
	addEdge(g, 2, 5, 1);
	addEdge(g, 4, 5, 1);

	g->foodSource = 4;
	g->hive = 0;
}



















