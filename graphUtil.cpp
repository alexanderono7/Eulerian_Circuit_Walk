#include "graph.h"
#include <iostream>
#define INF 99999

/* 
This file contains more complex algorithms/functions related to the graph structure defined in graph.h
*/

//Returns graph O, the derived graph of g which has odd-degree vertices
GRAPH *locateOddVertices(GRAPH *g)
{
    int *odds = new int[g->vertices + 1];
    int numOdd = 1; //this will be the number of vertices for graph O
    for (int i = 1; i < (g->vertices + 1); i++)
    {
        int v = 0; //counter for # vertices
        for (int j = 1; j < (g->vertices + 1); j++)
        {
            if (g->A[i][j] == 1)
                v++;
        }
        if (v % 2 == 1)
        {
            (odds[numOdd] = i);
            numOdd++;
        }
    }
    int oddEdges = (numOdd * numOdd) - numOdd;

    //dynamically allocate memory for (numOdd)x(numOdd) adjacency matrix
    // g->O = new int *[g->numOdd + 1];
    // for (int i = 1; i < (g->numOdd + 1); i++)
    // {
    //     g->O[i] = new int[g->numOdd + 1];
    // }
    GRAPH *O;
    O = Initialize(numOdd-1, oddEdges);

    for (int i = 0; i < numOdd; i++)
    {
        O->names[i] = odds[i];
    }
    delete[] odds;

    return O;
}

//Finds the distance of the shortest path between all pairs of vertices
//Then it applies this to the derivative graph
GRAPH *floydWarshall(GRAPH *g, GRAPH *o)
{
    int V = g->vertices;
    int **dist = new int *[V + 1];
    for (int a = 1; a < (V + 1); a++)
    {
        dist[a] = new int[V + 1];
    }
    
    dist = g->A;

    //F-W algo requires a distinction between "no path" (infinity) and "points to itself" (0), something I have learned the hard way...
    for (int a = 1; a < (V + 1); a++)
    {
        for (int b = 1; b < (V + 1); b++){
            if(dist[a][b] == 0) dist[a][b] = INF;
        }
        dist[a][a] = 0;
    }

    //actual floyd warshall algorithm
    for (int k = 1; k < (V + 1); k++)
    {
        for (int i = 1; i < (V + 1); i++)
        {
            for (int j = 1; j < (V + 1); j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    //update derived graph o
    for (int a = 1; a < (o->vertices + 1); a++)
    {
        for (int b = 1; b < (o->vertices + 1); b++)
        {
            o->A[a][b] = dist[o->names[a]][o->names[b]];
        }
    }

    //delete allocated memory
    for (int a = 1; a < (o->vertices + 1); a++)
    {
        delete[] dist[a];
    }
    delete[] dist;

    return o;
}

// MATCH *perfectMatching(GRAPH *o){

// }

// GRAPH *insertVirtuals(MATCH *m){

// }

// void euler(GRAPH *g){

// }