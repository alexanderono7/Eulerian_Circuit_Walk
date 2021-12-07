#include <iostream>
#include "graph.h"
#include "graphUtil.h"


/* 
Alexander Ono
amono1@asu.edu
CSE-310: Data Structure and Algorithms
Final Project (HW07)
*/
int main(){
    //variable declaration
    cout << "Program Executed\n";
    GRAPH *g = NULL; //primary graph
    GRAPH *o = NULL; //derived graph- for odd-degree vertices
    PATH *m = NULL; //perfect matching set of edges

    //Initialize graph g and populate it
    g = graphInput(g);
    g = initializeVirtuals(g, g->vertices);

    //Create derivative graph o consisting of odd-degree vertices from original graph g
    o = locateOddVertices(g);
    o = initializeVirtuals(o, g->vertices);

    //populate derivative graph g with shortest-path 
    o = floydWarshall(g, o);
    cout << "Results of Floyd-Warshall on O:\n";
    printMatrix(o->A,o->names,o->vertices); //print adjacency matrix of derived graph o
    g->virt = o->virt;

    //return a list of edges that form a minimum perfect matching from derived graph o
    m = perfectMatching(o); 
    cout << "The greedy perfect matching in O: M = ";
    printPath(m); //print path (path = structure, a list of EDGE objects)

    recoverPath(g, m, 14, 4);
    printPath(m); //print path (path = structure, a list of EDGE objects)


    //insert virtual edges as defined in PATH m into virt** (n by n virtual edge matrix object) as defined in graph g

    // deleteGraph(g);
    // deleteGraph(o);
    cout << "\nDone\n";
    exit(0);
}
