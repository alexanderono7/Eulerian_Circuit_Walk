#include "graph.h"

/* 
This file contains more complex algorithms/functions related to the graph structure defined in graph.h
*/

//Updates the array odd[] of the graph g to true or false for each index, corresponding to each vertex
GRAPH *locateOddVertices(GRAPH *g)
{
    for (int i = 1; i < (g->vertices + 1); i++)
    {
        int v = 0; //counter for # vertices
        for (int j = 1; j < (g->vertices + 1); j++)
        {
            (g->A[i][j] == 1) ?(++v):0; //For this value of i, increment v for all vertices it has an edge with (including negative edges)
        }
        g->odd[i] = (v % 2 == 1) ? (true) : (false);
    }
    return g;
}
