#include "graph.h"

GRAPH *locateOddVertices(GRAPH *g);
GRAPH *floydWarshall(GRAPH *g, GRAPH *o);
PATH *perfectMatching(GRAPH *o);
void printPath(PATH *p);
PATH *recoverPath(GRAPH *g, PATH *p, int u, int v);
GRAPH *initializeVirtuals(GRAPH *g, int n);
GRAPH *insertVirtuals(PATH *m, GRAPH *g);
PATH *initializePath(int n);
PATH *append(PATH *p, int u, int v, int W);
PATH *pop(PATH *p);