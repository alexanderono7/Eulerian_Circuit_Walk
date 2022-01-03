//created by Alexander Ono
#ifndef GRAPH_H_
#define GRAPH_H_

struct EDGE {
    int a;
    int b;
    int weight;
};

//List of EDGEs. Used for storing perfect matching, virtual edge paths, and euler circuit.
struct PATH {
    int quant;  //quantity
    EDGE *P;
};

//Structure that defines an undirected graph
struct GRAPH {
    int vertices;
    int edges;

    int *names;

    int **A;       //2 dimensional Adjacency matrix is used to show edge relationships, size is (vertices)x(vertices).
    int **virt;  //2 dimensional matrix of virtual paths, used for path recovery
    int **vA;  //2 dimensional virtual adj. matrix
};

GRAPH *graphInput(GRAPH *graph);
GRAPH *Initialize(int n, int m);
void printGraph(GRAPH *g);
void printMatrix(int **m, int *v, int n);
void deleteGraph(GRAPH *g);
void deleteVirt(GRAPH *g, int n);

using namespace std;

#endif
