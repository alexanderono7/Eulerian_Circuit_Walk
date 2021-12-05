#include <iostream>
#include "graph.h"

int main(){
    //variable declaration
    cout << "Program Executed\n";
    GRAPH *g = NULL;
    g = graphInput(g);



    deleteGraph(g);
    exit(0);
}