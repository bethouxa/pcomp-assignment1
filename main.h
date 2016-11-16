typedef unsigned int uint;

typedef struct
{
	uint** nodes;
	uint** pheromone;
	uint nbNodes;
} ACOGraph;

typedef struct
{
	uint position;

	uint* tabuNodes;
	uint nbTabuNodes;

}Ant;

void allocateAndInitializeACOGraphContents(ACOGraph* g);
void evaporatePheromones(ACOGraph* g);
void move(Ant* a, ACOGraph* g);
