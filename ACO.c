/**
 * All functions related to the ACO algorithm itself
 * belong here.
 */


void evaporatePheromones(ACOGraph* g)
{
	uint pRate = 0.5;
	for (int i = 0; i < g->nbNodes; ++i) {
		for (int j = 0; j < g->nbNodes; ++j) {
			g->edge[i][j]->pheromone = (1 - pRate) * g->edge[i][j]->pheromone;
		}
	}
}
