/**
 * All functions related to the data structures and representations
 * belong here.
 */

#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include <stdio.h>

const ACOEdge NullEdge =
{
	INF,
	0,
};

extern void allocateAndInitializeACOGraphContents(ACOGraph* g, int nbNodes)
/* Remember to assign a value to g.nbNodes */
{
	//g = malloc(sizeof(ACOGraph));

	g->nbNodes = nbNodes;

	g->edge = malloc(sizeof(ACOEdge**) * nbNodes);

	for (int i = 0; i < nbNodes; ++i)
	{
		g->edge[i] = malloc(sizeof(ACOEdge) * nbNodes);
		for(int j = 0; j < nbNodes; ++j)
		g->edge[i][j] = NullEdge;
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
	ACOEdge* res = g->edge[nodeId];
	return res;
}

void addEdge(ACOGraph* g, uint from, uint to, float weight)
{
	ACOEdge e = {weight, 0};
	g->edge[from][to] = e;
	g->edge[to][from] = e;
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

void addPheromone(ACOGraph* g, uint from, uint to)
{
	g->edge[from][to].pheromone++;
	g->edge[to][from].pheromone++;

}

uint getHivePosition(ACOGraph* g) 
{
	return g->hive;
}

bool isFoodSource(ACOGraph* g, uint node)
{
	return node == g->foodSource;
}

bool isTabu(Ant* a, uint nodeId)
{
	bool res = false;
	for (int i=0; i<a->nbTabuNodes; ++i)
		if (nodeId == a->tabuNodes[i]) res = true;
	return res;
}

void initAnts(ACOGraph* g, Ant* a, uint nb_ants)
{
	for(int i=0; i<nb_ants; ++i)
	{
		a[i].hasFoundFood = false;
		a[i].nbTabuNodes = 0;
		a[i].tabuNodes = NULL;
		a[i].position = g->hive;
		a[i].displ_index = i;
		a[i].wasInDeadEnd = false;
	}
}

void resetAnt(ACOGraph* g, Ant* a)
{
	uint old_displ_index = a->displ_index;
	initAnts(g, a, 1);
	a->displ_index = old_displ_index+100;
	printf("\nAnt #%d has been reset, is now #%d", old_displ_index, a->displ_index);

}

void addTabuNode(Ant* a, uint nodeId)
{
	a->nbTabuNodes = a->nbTabuNodes+1;
	a->tabuNodes = realloc(a->tabuNodes, sizeof(uint)*a->nbTabuNodes);
	a->tabuNodes[a->nbTabuNodes-1] = nodeId;
}

uint popTabuNode(Ant* a)
{
	uint res = a->tabuNodes[a->nbTabuNodes-1];
	a->nbTabuNodes--;
	a->tabuNodes = realloc(a->tabuNodes, sizeof(uint)*a->nbTabuNodes);
	return res;
}

void clearTabuNodes(Ant* a)
{
	a->nbTabuNodes = 0;
	a->tabuNodes = realloc(a->tabuNodes, sizeof(uint)*a->nbTabuNodes);
}

void printArray(uint* array, uint elems)
{
	for(int i=0; i<elems; ++i)
		printf("%d", array[i]);
}
