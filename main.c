#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#include "main.h"

#define INF INT_MAX

ACOGraph* g;

void populateTestData(ACOGraph* g);

int main(int argc, char const *argv[])
{
	uint nb_ants, targetIter;
	if (argc < 3 || argc > 4)
	{
		printf("Usage: ./ACO <number of threads (=number of ants)> <number of iterations>");
		return -2;
	}

	nb_ants = atoi(argv[1]);
	targetIter = atoi(argv[2]);

	g = calloc(1,sizeof(ACOGraph));
	Ant* ants = calloc(nb_ants, sizeof(Ant));

	initAnts(g, ants, nb_ants);
	allocateAndInitializeACOGraphContents(g, 6);
	srand((unsigned) time(NULL));

	populateTestData(g);

	pthread_t* thread_handles = malloc(sizeof(pthread_t)*nb_ants);

	uint iterCount = 0;
	while(iterCount < targetIter)
	{
		printf("########## TICK %d #########", iterCount);
		for(uint antIndex=0; antIndex<nb_ants; ++antIndex)
		{
			pthread_create(&thread_handles[antIndex], NULL, move, &ants[antIndex]);
		}
		for(uint antIndex=0; antIndex<nb_ants; ++antIndex)
		{
			pthread_join(thread_handles[antIndex], NULL);
			// Reset ant if it has made a full trip (found food & came back to hive)
			if (ants[antIndex].hasFoundFood && ants[antIndex].position == getHivePosition(g))
				resetAnt(g, &ants[antIndex]);
		}
		printf("\n");
		evaporatePheromones(g);
		iterCount++;
	}
	printStrongestPheromoneTrail(g,0);
	printf("\n");
	fflush(stdout);

	freeACOGraph(g);
	free(thread_handles);
	free(ants);

	return 0;

}


void populateTestData(ACOGraph* g)
{
	addEdge(g, 0, 1, 1.0);
	addEdge(g, 0, 3, 1.0);
	addEdge(g, 1, 2, 1.0);
	addEdge(g, 1, 3, 1.0);
	addEdge(g, 3, 2, 1.0);
	addEdge(g, 3, 4, 1.0);
	addEdge(g, 2, 5, 1.0);
	addEdge(g, 4, 5, 1.0);

	g->foodSource = 4;
	g->hive = 0;
}



















