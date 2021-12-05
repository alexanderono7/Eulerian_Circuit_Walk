#ifndef GRAPH_H_
#define GRAPH_H_

//Structure that defines an undirected graph
struct GRAPH
{
    int vertices;
    int edges;
    int **A; //2 dimensional graph is used to show edge relationships, size is (vertices)x(vertices).
    //A stands for Adjacency Matrix
    bool *odd; //1 dimensional graph used to track which vertices are of an odd (True) or even (False) degree
};

GRAPH *graphInput(GRAPH *graph);
void printGraph(GRAPH *g);
void deleteGraph(GRAPH *g);

using namespace std;

#endif
