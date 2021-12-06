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
    GRAPH *g = NULL;
    GRAPH *o = NULL;


    g = graphInput(g);
    printGraph(g);

    o = locateOddVertices(g);
    o = floydWarshall(g, o);
    printMatrix(o->A,o->names,o->vertices); //print adjacency matrix of derived graph O
    


    // deleteGraph(g);
    // deleteGraph(o);
    cout << "Done\n";
    exit(0);
}
