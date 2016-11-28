/**
 * All functions related to the data structures and representations
 * belong here.
 */

#include <stdlib.h>

void allocateAndInitializeACOGraphContents(ACOGraph* g)
/* Remember to assign a value to g.nbNodes */
{
	g->nodes = malloc(sizeof(ACOEdge**) * g.nbNodes);

	for (int i = 0; i < g.nbNodes; ++i)
	{
		g->nodes[i] = malloc(sizeof(ACOEdge*) * g.nbNodes);

		for (int j = 0; j < g.nbNodes; ++j)
		{
			g->nodes[i][j] = NULL;
		}
	}

}

void freeACOGraph(ACOGraph* g)
{
	for (int i = 0; i < g.nbNodes; ++i)
	{
		for (int j = 0; j < g.nbNodes; ++j)
		{
			free(g->nodes[i][j]);
		}
		free(g->nodes[i]);
	}
	free(g->nodes);

	free(g);
}

