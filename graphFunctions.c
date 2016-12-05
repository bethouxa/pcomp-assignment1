/**
 * All functions related to the data structures and representations
 * belong here.
 */

#include <stdlib.h>
#include "main.h"

extern void allocateAndInitializeACOGraphContents(ACOGraph* g, int nbNodes)
/* Remember to assign a value to g.nbNodes */
{
	g = malloc(sizeof(ACOGraph));

	g->nbNodes = nbNodes;

	g->edge = malloc(sizeof(ACOEdge**) * nbNodes);

	for (int i = 0; i < nbNodes; ++i)
	{
		g->edge[i] = malloc(sizeof(ACOEdge*) * nbNodes);

		for (int j = 0; j < nbNodes; ++j)
		{
			g->edge[i][j] = calloc(1,sizeof(ACOEdge)); // Allocate and initialize to NULL all edges
		}
	}
}


extern void freeACOGraph(ACOGraph* g)
{
	for (int i = 0; i < g->nbNodes; ++i)
	{
		for (int j = 0; j < g->nbNodes; ++j)
		{
			free(g->edge[i][j]); // Free one ACOEdge*
		}
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

extern double getPheromone(ACOGraph* g, uint x, uint y)
{
	return (g->edge[x][y]->pheromone);
}

uint getHivePosition(ACOGraph* g) 
{
	return g->hive;
