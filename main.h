#ifndef MAIN_H
#define MAIN_H

typedef unsigned int uint;
typedef unsigned char bool;

typedef struct
{
	uint weight;
	uint pheromone;
	
} ACOEdge;

typedef struct
{
	ACOEdge*** edge; // 2D array of ACOEdge* (adjacency matrix)
	uint nbNodes;
	uint hive;
	bool *foodSource;
} ACOGraph;


typedef struct
{
	uint position;
	bool hasFoundFood;
	uint* tabuNodes;
	uint nbTabuNodes;

}Ant;

// ######### GRAPH FUNCTIONS ##########

/**
 * Allocates and initializes the graph representation with the correct amount of
 * nodes
 *
 * @param      g        the graph to initialize
 * @param[in]  nbNodes  The number of nodes
 */
void allocateAndInitializeACOGraphContents(ACOGraph* g, int nbNodes);


/**
 * @brief      Frees an ACOGrap
 *
 * @param      g     the graph to free
 */
void freeACOGraph(ACOGraph* g);

/**
 * @brief      Gets the edges connected to the given node
 *
 * @param      g       The ACOgraph we're using
 * @param[in]  nodeId  The node identifier
 *
 * @return     An array of g->nbNodes ACOEdges with NULL values if an edge
 *             doesn't exist.
 */	
ACOEdge** getEdges(ACOGraph* g, uint nodeId);

/**
 * @brief      Gets the pheromone level between two nodes
 *
 * @param      g     The graph we're using
 * @param[in]  x     One of the nodes connected to the edge
 * @param[in]  y     The other node connected to the edge
 *
 * @return     The pheromone level
 */
double getPheromone(ACOGraph* g, uint x, uint y);

/**
 * @brief      Gets the hive position.
 *
 * @param      g     The graph we're using
 *
 * @return     The hive position.
 */
uint getHivePosition(ACOGraph* g);
/**
 * @brief      Determines if the given node is food source.
 *
 * @param      g       Graph we're using
 * @param[in]  nodeId  The node identifier
 */
void isFoodSource(ACOGraph* g, uint nodeId);



/**
 * @brief      Picks the next node for the given ant.
 * 
 * This function picks the next node for a given ant. It will compute the probability
 * of going though each edge using it's pheromone level and weight, then will 
 * pick an edge through a random weighted choice.
 *
 * @param[in]  ant   The ant
 * @param      g     Graph we're using
 *
 * @return     The id of the node where the ant will head next
 */
ACOEdge chooseEdges(Ant ant, ACOGraph* g);
void evaporatePheromones(ACOGraph* g);

/**
 * @brief Move the ant to the next node
 * 
 * Moves the ant to the next node in it's path (see chooseEdges()), updates pheromones when needed,
 * updates ant.hasFoundFood if needed.
 * @param 	ant		The ant to move
 * @param 	g 		graph we're using
 */
void move(Ant ant, ACOGraph* g);


#endif