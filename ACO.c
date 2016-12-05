/**
 * All functions related to the ACO algorithm itself
 * belong here.
 */

#include<stdlib.h>

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

/**
 * Prints the trail with the highest amount of pheromones.
 *
 * @param g
 * @param startNode
 */
void printStrongestPheromoneTrail(ACOGraph* g, uint startNode)
{
	printStrongestPheromoneTrailWorker(g, startNode, -1);
}
void printStrongestPheromoneTrailWorker(ACOGraph* g, uint rootNode, int parentNode)
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
	ACOEdge edges[g->nbNodes];

	edges = getEdges(g, rootNode);

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
		printStrongestPheromoneTrailWorker(g, nextNode, rootNode);
}

/**
* Move the ant
* If ant has ever found food update pheromones
* If ant is on a food source update ant.hasFoundFood
*/

/*
current position
get adjacent edges
if edge = tabunodes, ignore that edge
ant[i] chose edge
ant[i] change position to chosen edge
if position = food source, update hasfoundfood
if ant has found food = true, deposit pheromone on position, add position to tabu nodes


*/
void move(Ant ant, ACOGraph* g) {
	uint chosenEdge = chooseEdges(ant, g);
	ant.position = chosenEdge;	
	if (ant.hasFoundFood = true) {
		chosenEdge.pheromones++;
		ant.tabuNodes = ant.position;
	}
	if (ant.position = chosenEdge.isFoodSource)
		ant.hasFoundFood = true;
}

/*Choose Edge*/
ACOEdge chooseEdges(Ant ant, ACOGraph* g) {
	getEdges(g, ant.position);
	int i;
	for (i = 0; i < g->edge.length; i++) {
		float attractiveness[i] = g->edge[i]->pheromone*g->edge[i]->weight;
		float totalAtt = 0;
			totalAtt += attractiveness[i];			
	}
	for (i = 0; i < g->edge.length; i++)
		float probability[i] = attractiveness[i] / totalAtt;

	return g->edge;
}