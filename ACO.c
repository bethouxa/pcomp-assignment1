/**
 * All functions related to the ACO algorithm itself
 * belong here.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"

#define min(a,b) ((a)>(b)?(a):(b));

void evaporatePheromones(ACOGraph* g)
{
	float pRate = 0.5;
	for (int i = 0; i < g->nbNodes; ++i) {
		for (int j = 0; j < g->nbNodes; ++j) {
			g->edge[i][j].pheromone = (1.0 - pRate) * (g->edge[i][j].pheromone);
		}
	}
}


void _printStrongestPheromoneTrailWorker(ACOGraph* g, uint rootNode, int parentNode)
{
	fflush(stdout);
	/*
	 * - get all edges attached to current node
	 * - pick the edge with the highest pheromone level
	 * - display the node attached to this edge
	 * - recurse
	 */
	printf("%d", rootNode);

	float maxPheromone = 0;
	uint nextNode;
	bool hasChildren = 0;
	ACOEdge* edges = getEdges(g, rootNode);

	if (isFoodSource(g, rootNode))
	{
		fflush(stdout);
		return;
	}
	for(int i=0; i<=g->nbNodes; ++i)
	{
		if (!isNullEdge2(&edges[i]) && i!=parentNode && edges[i].pheromone > maxPheromone)
		// if existing edge, not parent node (to avoid going back & forth), and pheromone higher than local maximum
		{
			hasChildren = 1;
			maxPheromone = edges[i].pheromone;
			nextNode = i;
		}
	}
	if(hasChildren)
	{
		printf(" -> ");
		_printStrongestPheromoneTrailWorker(g, nextNode, rootNode);
	}
}


/**
 * Prints the trail with the highest amount of pheromones.
 *
 * @param g
 * @param startNode
 */
void printStrongestPheromoneTrail(ACOGraph* g, uint startNode)
{
	_printStrongestPheromoneTrailWorker(g, startNode, -1);
}


/*
current position
get adjacent edges
if edge = tabunodes, ignore that edge
ant[i] chose edge
ant[i] change position to chosen edge
if position = food source, update hasfoundfood
if ant has found food = true, deposit pheromone on position, add position to tabu nodes


*/
void move(Ant* ant, ACOGraph* g) {

	if (isFoodSource(g, ant->position))
	{
		ant->hasFoundFood = true;
		clearTabuNodes(ant); // So we don't have to take an entirely different path to come back
	}


	printf("\nMoving ant #%d:", ant->displ_index);

	uint nextNode = chooseEdges(ant, g);
	if (nextNode == INF) // Special value meaning that the ant is in a deep dead end and should be reset
	{
		int old_displ_index = ant->displ_index;
		resetAnt(g, ant);
		printf("Ant #%d was in a deep dead end and was reset, it is now ant #%d", old_displ_index, ant->displ_index);
		return;
	}
	printf(" from node %d to node %d", ant->position, nextNode);
	if (isFoodSource(g, nextNode)) printf(" (food source!)");

	// Checks if we found food (we can't find food twice as the food node will be tabu from now on

	// Increase pheromones if have found food
	if (ant->hasFoundFood == true) {
		printf(" w/ pheromone trail");
		addPheromone(g, ant->position, nextNode);
	}



	// Current node becomes tabu
	addTabuNode(ant, ant->position);
	// The actual move
	ant->position = nextNode;

	fflush(stdout);
}

uint chooseEdges(Ant* ant, ACOGraph* g) {
	
	uint i;
	float rawAttr;
	float attractiveness[g->nbNodes];
	float probability[g->nbNodes];
	float totalAtt = 0.0;

	ACOEdge* edge = getEdges(g, ant->position); // get all adges connected to the node where the ant is

	for (i = 0; i < g->nbNodes; i++) {
		// Compute attractiveness of a node
		if ( !(isNullEdge2(&edge[i]) || isTabu(ant, i)) ) // if edge not null and not tabu
		{
			rawAttr = (edge[i].pheromone) * (1/edge[i].weight);
			attractiveness[i] = rawAttr > 0.5 ? rawAttr : 0.5;
		}
		else 
			attractiveness[i] = 0.0;
		// Add it to the total attractiveness of the surrounding nodes
		totalAtt += attractiveness[i];
	}

	// Dead-end management
	if (totalAtt == 0.0) // This only happens if we're in a dead-end
	{
		if (!ant->wasInDeadEnd)
		{
			printf(" we're in a dead end / blocked by tabu nodes, going back");
			ant->wasInDeadEnd = true;
			return popTabuNode(ant);
		}
		else // We're in a deep dead end, tell move() to reset the ant
		{
			return INF;
		}
	}
	else {
		ant->wasInDeadEnd = false;
	}

	// Pick an edge w/ a random choice weighted by attractivity
	for (i = 0; i < g->nbNodes; i++)
	{
		probability[i] = attractiveness[i] / totalAtt;
	}
	float r = (float)rand() / (float)RAND_MAX; // get a value in [0;1]
	float icf = 0.0; // increasing cumulative frequency
	uint chosenEdge;
	for (i = 0; i < g->nbNodes; i++)
	{
		icf += probability[i];
		if (r <= icf)
		{
			chosenEdge = i;
			break;
		}
	}
	

	return chosenEdge;
}
