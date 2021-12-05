

#include <iostream>
#include "graph.h"

/*
This file contains basic functions related to the graph structure defined in graph.h
*/
int splitHalf1(string s);
int splitHalf2(string s);
GRAPH *Initialize(int n, int m);
GRAPH *assignEdge(GRAPH *g, int u, int v, int weight);

GRAPH *graphInput(GRAPH *g)
{
    int n;    //n = number of vertices in graph G
    int m;    //m = number of edges in graph G
    string s; //input string

    getline(cin, s); //retrieve initial input for ed

    n = splitHalf1(s);
    m = splitHalf2(s);

    g = Initialize(n, m);

    //Take the m edges in the rest of the file and assign them to the graph
    for (int i = 0; i < m; i++)
    {
        getline(cin, s);
        g = assignEdge(g, splitHalf1(s), splitHalf2(s), 1);
    }

    return g;
}

//for a string that is composed of two numbers separated by a single space char, split them and return both.
int splitHalf1(string s)
{
    return stoi(s.substr(0, s.find_first_of(' ')));
}
int splitHalf2(string s)
{
    return stoi(s.substr((s.find_first_of(' ') + 1), s.length()));
}

//Initialize empty graph
//The attributes odd[] and O[][] are instantiated in the locateOddVertices() function of graphUtil.cpp, not here.
GRAPH *Initialize(int n, int m)
{
    GRAPH *newGraph = new GRAPH; //newGraph is pointer to new graph object created
    newGraph->vertices = n;
    newGraph->edges = m;
    newGraph->numOdd = 0;

    // dynamically create an array of pointers of size n+1
    newGraph->A = new int *[n + 1];
    newGraph->dist = new int *[n + 1];
    newGraph->odd = new int[n + 1];

    for (int i = 0; i < (n + 1); i++)
    {
        // dynamically allocate memory of size n+1 for each row (n by n matrix)
        newGraph->A[i] = new int[n + 1];
        newGraph->dist[i] = new int[n + 1];

        newGraph->A[0][i] = i; //store the "names" of the nodes in the 0th array (which in unused in the adj. matrix)
        for (int j = 0; j < n + 1; j++)
        {
            
            //set value of each point of both matrices to 0
            newGraph->A[i][j] = 0;
            newGraph->dist[i][j] = 0;
        }
    }

    //remove later
    // // set all values of the adjacency matrix to 0
    // for (int i = 1; i < n + 1; i++)
    // {
    //     for (int j = 1; j < n + 1; j++)
    //     {
    //         newGraph->A[i][j] = 0;
    //     }
    // }

    return newGraph;
}

//Given the values of two vertices, create an edge between them
//(update & return graph)
GRAPH *assignEdge(GRAPH *g, int u, int v, int weight)
{
    g->A[u][v] = weight;
    g->A[v][u] = weight;
    return g;
}

//Print out (n x n) matrix (m)
// v = array of the labels
void printMatrix(int **m, int *v, int n)
{
    cout << "     |  ";
    for (int i = 1; i < (n + 1); i++)
    {
        printf("%3d ", i);
    }
    cout << "\n--- -+-";
    for (int i = 1; i < (n + 1); i++)
    {
        cout << " ---";
    }
    cout << "\n";

    for (int i = 1; i < (n + 1); i++)
    {
        for (int j = 1; j < (n + 1); j++)
        {
            if (j == 1)
            {
                printf("%3d  |  ", i);
            }
            printf("%3d ", m[i][j]);
        }
        cout << endl;
    }
    return;
}

// deallocate memory for graph
void deleteGraph(GRAPH *g)
{
    //delete regular adjacency matrix
    for (int i = 0; i < (g->vertices + 1); i++)
    {
        delete[] g->A[i];
        delete[] g->dist[i];
    }
    //delete odd adjacency matrix, if it was created
    if (g->O != NULL)
    {
        for (int i = 0; i < (g->numOdd + 1); i++)
        {
            delete[] g->O[i];
        }
    }
    delete[] g->A;
    delete[] g->odd;
}
