#include <iostream>
#include "graph.h"

using namespace std;

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
GRAPH *Initialize(int n, int m)
{
    GRAPH *newGraph = new GRAPH; //newGraph is pointer to new graph object created

    newGraph->vertices = n;
    newGraph->edges = m;
    // dynamically create an array of pointers of size n+1
    newGraph->A = new int *[n + 1];
    // dynamically allocate memory of size n+1 for each row (n by n matrix)
    for (int i = 1; i < (n + 1); i++)
    {
        newGraph->A[i] = new int[n + 1];
    }

    // set all values of the adjacency matrix to 0
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            newGraph->A[i][j] = 0;
        }
    }

    return newGraph;
}

//Given the values of two vertices, create an edge between them
GRAPH *assignEdge(GRAPH *g, int u, int v, int weight)
{
    g->A[u][v] = weight;
    g->A[v][u] = weight;
    return g;
}

//Old Version - remove later
// //Print out the graph adjacency matrix
// void printGraph(GRAPH *g)
// {
//     for (int i = 1; i < (g->vertices + 1); i++)
//     {
//         for (int j = 1; j < (g->vertices + 1); j++)
//         {
//             cout << g->A[i][j] << " ";
//         }
//         cout << endl;
//     }
//     return;
// }

//Print out the graph adjacency matrix
void printGraph(GRAPH *g)
{
    cout << "  ";
    for (int i = 1; i < (g->vertices + 1); i++)
    {
        cout << i << " ";
    }
    cout << "\n";

    for (int i = 1; i < (g->vertices + 1); i++)
    {
        for (int j = 1; j < (g->vertices + 1); j++)
        {
            if (j == 1)
            {
                cout << i << " ";
            }
            cout << g->A[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

// deallocate memory for graph argument
void deleteGraph(GRAPH *g)
{
    for (int i = 0; i < (g->vertices + 1); i++)
    {
        delete[] g->A[i];
    }
    delete[] g->A;
}
