#include <iostream>
#include "graph.h"

using namespace std;

int main(){
    //variable declaration
    cout << "Program Executed\n";
    GRAPH *g = NULL;
    g = graphInput(g);
    printGraph(g);

    deleteGraph(g);
    exit(0);
}