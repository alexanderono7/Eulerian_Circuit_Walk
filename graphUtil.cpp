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
            (g->A[i][j] == 1) ? (++v) : 0; //For this value of i, increment v for all vertices it has an edge with (including negative edges)
        }
         (v % 2 == 1) ? (g->odd[g->numOdd] = i):0; //Set corresponding index of vertex to true if it is odd
        g->numOdd++;
    }

    //dynamically allocate memory for (numOdd)x(numOdd) adjacency matrix
    g->O = new int *[g->numOdd + 1];
    for (int i = 1; i < (g->numOdd + 1); i++)
    {
        g->O[i] = new int[g->numOdd + 1];
    }

    return g;
}

//Finds the distance of the shortest path between all pairs of vertices
GRAPH *floydWarshall(GRAPH *g)
{
    int V = g->vertices;
    int **dist = g->A;
    for (int k = 1; k < (V + 1); k++){
        for (int i = 1; i < (V + 1); i++){
            for (int j = 1; j < (V + 1); j++){
                if (dist[i][j]>dist[i][k]+dist[k][j])
                {
                    dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
        }
    }

    g->dist = dist;
    return g;
}
