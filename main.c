#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include "main.h"

#define INF INT_MAX

int main(int argc, char const *argv[])
{
	ACOGraph testGraph;
	testGraph.nbNodes = 7;
	allocateAndInitializeACOGraphContents(&testGraph);

	return 0;
}

