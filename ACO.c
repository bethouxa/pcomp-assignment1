/**
 * All functions related to the ACO algorithm itself
 * belong here.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"


void evaporatePheromones(ACOGraph* g)
{
	uint pRate = 0.5;
	for (int i = 0; i < g->nbNodes; ++i) {
		for (int j = 0; j < g->nbNodes; ++j) {
			g->edge[i][j]->pheromone = (1 - pRate) * g->edge[i][j]->pheromone;
		}
	}
}


void _printStrongestPheromoneTrailWorker(ACOGraph* g, uint rootNode, int parentNode)
{
	/*
	 * - get all edges attached to current node
	 * - pick the edge with the highest pheromone level
	 * - display the node attached to this edge
	 * - recurse
	 */
	printf("%d", rootNode);

	int maxPheromone = 0;
	uint nextNode;
	bool hasChildren = 0;
	ACOEdge** edges = getEdges(g, rootNode);

	for(int i=0; i<=g->nbNodes; ++i)
	{
		if (edges[i] != NULL && i!=parentNode && edges[i]->pheromone > maxPheromone)
		{
			hasChildren = 1;
			maxPheromone = edges[i]->pheromone;
			nextNode = i;
		}
	}
	if(hasChildren)
		printf(" -> ");
		_printStrongestPheromoneTrailWorker(g, nextNode, rootNode);
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
	uint nextNode = chooseEdges(ant, g);
	if (ant->hasFoundFood == true) {
		g->edge[ant->position][nextNode]->pheromone++;
		// Make tabuNodes grow and add the current position as tabu
		ant->tabuNodes = realloc(ant->tabuNodes, sizeof(uint)+(ant->nbTabuNodes)+1);
		ant->nbTabuNodes++;
		ant->tabuNodes[ant->nbTabuNodes] = ant->position;
	}

	ant->position = nextNode;	
	
	if (isFoodSource(g, ant->position))
		ant->hasFoundFood = true;
}

uint chooseEdges(Ant* ant, ACOGraph* g) {
	
	uint i;
	float attractiveness[g->nbNodes];
	float probability[g->nbNodes];
	float totalAtt;

	ACOEdge** edge; edge = g->edge[ant->position]; // get all adges connected to the node where the ant is

	for (i = 0; i < g->nbNodes; i++) {
		// Compute attractiveness of a node
		if (edge != NULL)
			attractiveness[i] = (edge[i]->pheromone) * (edge[i]->weight);
		else 
			attractiveness[i] = 0.0;
		// Add it to the total attractiveness of the surrounding nodes
		float totalAtt = 0;
			totalAtt += attractiveness[i];
	}
	for (i = 0; i < g->nbNodes; i++)
	{	
		probability[i] = attractiveness[i] / (totalAtt - attractiveness[i]);
		//                     attr. of this node / attr. of *the other* nodes
	}
	// random choice weighted by the probability array
	float sumProbability;
	for (i = 0; i < g->nbNodes; i++) sumProbability += probability[i];
	// Change probabilities so that their sum is equal to 1
	for (i = 0; i < g->nbNodes; i++) probability[i] /= sumProbability;


	// Pick an edge w/ a random weighted choice
	srand((unsigned) time(NULL));
	float r = (float)rand() / (float)RAND_MAX;
	float icf = 0; // increasing cumulative frequency
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