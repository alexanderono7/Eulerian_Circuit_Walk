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

//Virtual edge struct - includes recorded path
struct VEDGE {
    int weight;
    PATH path;
};

//Structure that defines an undirected graph
struct GRAPH {
    int vertices;
    int edges;

    int *names;

    int **A;       //2 dimensional Adjacency matrix is used to show edge relationships, size is (vertices)x(vertices).
    int **virt;  //2 dimensional matrix of virtual edges
};

GRAPH *graphInput(GRAPH *graph);
GRAPH *Initialize(int n, int m);
void printGraph(GRAPH *g);
void printMatrix(int **m, int *v, int n);
void deleteGraph(GRAPH *g);

using namespace std;

#endif
