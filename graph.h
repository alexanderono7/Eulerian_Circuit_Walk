#ifndef GRAPH_H_
#define GRAPH_H_

//Structure that defines an undirected graph
struct GRAPH
{
    int vertices;
    int edges;

    int **A; //2 dimensional Adjacency matrix is used to show edge relationships, size is (vertices)x(vertices).
    int **dist; //2 dimensional minimum distance matrix, size is (vertices)x(vertices).

    int numOdd; //quantity of odd vertices
    int *odd; //1 dimensional graph used to track which vertices are of an odd or even degree
    int *oddName; //list of values of odd vertices
    int **O; //Odd 2 dimensional adjacency matrix
};

GRAPH *graphInput(GRAPH *graph);
void printMatrix(int **m, int *v, int n);
void deleteGraph(GRAPH *g);

using namespace std;

#endif
