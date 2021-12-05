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


    g = graphInput(g);
    g = locateOddVertices(g);
    for (int i = 1; i < g->vertices + 1; i++)
    {
        cout << i << " : " << g->odd[i] << "\n";
    }

    deleteGraph(g);
    cout << "Done\n";
    exit(0);
}
