typedef unsigned int uint;
typedef unsigned char bool;

typedef struct
{
	ACOEdge*** nodes; // 2D array of ACOEdge* (adjacency array)
	uint nbNodes;
} ACOGraph;

typedef struct
{
	uint weight;
	uint pheromone;
	bool isFoodSource;
}ACOEdge;

typedef struct
{
	uint position;
	bool hasFoundFood;
	uint* tabuNodes;
	uint nbTabuNodes;

}Ant;

void allocateAndInitializeACOGraphContents(ACOGraph* g);
void evaporatePheromones(ACOGraph* g);

/**
 * Move the ant
 * If ant has ever found food update pheromones
 * If ant is on a food source update ant.hasFoudFood
 */
void move(/* ? */);


