#include "graph.h"

GRAPH *locateOddVertices(GRAPH *g);
GRAPH *floydWarshall(GRAPH *g, GRAPH *o);
PATH *perfectMatching(GRAPH *o);
void printPath(PATH *p);
void recoverPath(GRAPH *g, PATH *p, int u, int v);

GRAPH *initializeVirtuals(GRAPH *g, int n);