/**
 * All functions related to the data structures and representations
 * belong here.
 */

#include <stdlib.h>
#include <stdbool.h>
#include "main.h"

const ACOEdge NullEdge =
{
	INF,
	0,
};

extern void allocateAndInitializeACOGraphContents(ACOGraph* g, int nbNodes)
/* Remember to assign a value to g.nbNodes */
{
	g = malloc(sizeof(ACOGraph));

	g->nbNodes = nbNodes;

	g->edge = malloc(sizeof(ACOEdge**) * nbNodes);

	for (int i = 0; i < nbNodes; ++i)
	{
		g->edge[i] = malloc(sizeof(ACOEdge) * nbNodes);
	}
}


extern void freeACOGraph(ACOGraph* g)
{
	for (int i = 0; i < g->nbNodes; ++i)
	{
		free(g->edge[i]); // Free a row of the matrix
	}
	free(g->edge); // Free the pointer to the matrix

	free(g); // Free the structure itself
	g = NULL;
}


extern ACOEdge* getEdges(ACOGraph* g, uint nodeId)
{
	return g->edge[nodeId];
}

bool isNullEdge(ACOGraph* g, uint fromNode, uint toNode)
{
	return isNullEdge2(&getEdges(g, fromNode)[toNode]);
}

bool isNullEdge2(ACOEdge* e)
{
	return e->pheromone == 0 && e->weight == INF;
}

extern double getPheromone(ACOGraph* g, uint x, uint y)
{
	return (g->edge[x][y].pheromone);
}

uint getHivePosition(ACOGraph* g) 
{
	return g->hive;
}

bool isFoodSource(ACOGraph* g, uint node)
{
	return node == g->foodSource;
}
