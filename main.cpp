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

    g = graphInput(g);
    // printGraph(g); //print main graph g

    o = locateOddVertices(g);
    o = floydWarshall(g, o);
    cout << "Results of Floyd-Warshall on O:\n";
    printMatrix(o->A,o->names,o->vertices); //print adjacency matrix of derived graph o
    m = perfectMatching(o); //return a list of edges that form a minimum perfect matching from derived graph o
    cout << "The greedy perfect matching in O: M = ";
    printPath(m);


    // deleteGraph(g);
    // deleteGraph(o);
    cout << "\nDone";
    exit(0);
}
