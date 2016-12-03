typedef unsigned int uint;
typedef unsigned char bool;

typedef struct
{
	uint weight;
	uint pheromone;
	bool isFoodSource;
} ACOEdge;

typedef struct
{
	ACOEdge*** edge; // 2D array of ACOEdge* (adjacency matrix)
	uint nbNodes;
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
 * Allocates and initializes the graph representation with the correct amount of nodes
 */
void allocateAndInitializeACOGraphContents(ACOGraph* g, int nbNodes);
void freeACOGraph(ACOGraph* g);
ACOEdge* getEdges(ACOGraph* g, uint nodeId);
double getPheromone(ACOGraph* g, uint x, uint y);



void evaporatePheromones(ACOGraph* g);

/**
 * Move the ant
 * If ant has ever found food update pheromones
 * If ant is on a food source update ant.hasFoudFood
 */
void move(/* ? */);


