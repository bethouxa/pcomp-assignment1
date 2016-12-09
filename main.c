#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "main.h"

#define INF INT_MAX

#define NB_SIMUL_ANTS 1

int main(int argc, char const *argv[])
{
	ACOGraph* g = NULL;
	Ant ants[NB_SIMUL_ANTS];

	allocateAndInitializeACOGraphContents(g, 8);

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
