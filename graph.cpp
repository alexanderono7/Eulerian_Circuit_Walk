

#include "graph.h"

#include <iostream>

/*
This file contains basic functions related to the graph structure defined in graph.h
*/
int splitHalf1(string s);
int splitHalf2(string s);
GRAPH *Initialize(int n, int m);
GRAPH *assignEdge(GRAPH *g, int u, int v, int weight);

GRAPH *graphInput(GRAPH *g) {
    int n;     //n = number of vertices in graph G
    int m;     //m = number of edges in graph G
    string s;  //input string

    getline(cin, s);  //retrieve initial input for ed

    n = splitHalf1(s);
    m = splitHalf2(s);

    g = Initialize(n, m);

    //Take the m edges in the rest of the file and assign them to the graph
    for (int i = 0; i < m; i++) {
        getline(cin, s);
        g = assignEdge(g, splitHalf1(s), splitHalf2(s), 1);
    }
    return g;
}

//for a string that is composed of two numbers separated by a single space char, split them and return both.
int splitHalf1(string s) {
    return stoi(s.substr(0, s.find_first_of(' ')));
}
int splitHalf2(string s) {
    return stoi(s.substr((s.find_first_of(' ') + 1), s.length()));
}

//Initialize empty graph
//The attributes odd[] and O[][] are instantiated in the locateOddVertices() function of graphUtil.cpp, not here.
GRAPH *Initialize(int n, int m) {
    GRAPH *newGraph = new GRAPH;  //newGraph is pointer to new graph object created
    newGraph->vertices = n;
    newGraph->edges = m;

    // dynamically create an array of pointers of size n+1
    newGraph->A = new int *[n + 1];
    newGraph->vA = new int *[n + 1];
    newGraph->names = new int[n + 1];

    //initialize subarrays of 2d arrays
    for (int i = 1; i < (n + 1); i++) {
        newGraph->A[i] = new int[n + 1];
        newGraph->vA[i] = new int[n + 1];
        newGraph->names[i] = i;
    }

    // set all values of the adjacency matrix to 0
    for (int i = 1; i < n + 1; i++) {
        newGraph->names[i] = i;  //name assignment; This variable exists because the odd-vertex graphs would be able to have their names be the same as their indices.

        for (int j = 1; j < n + 1; j++) {
            newGraph->A[i][j] = 0;
            newGraph->vA[i][j] = 0;
        }
    }

    return newGraph;
}

//Given the values of two vertices, create an edge between them
//(update & return graph)
GRAPH *assignEdge(GRAPH *g, int u, int v, int weight) {
    g->A[u][v] = weight;
    g->A[v][u] = weight;
    return g;
}

//Print out (n x n) matrix (m)
// v = array of the labels
void printMatrix(int **m, int *v, int n) {
    cout << "\n     |  ";
    for (int i = 1; i < (n + 1); i++) {
        printf("%3d ", v[i]);
    }
    cout << "\n--- -+-";
    for (int i = 1; i < (n + 1); i++) {
        cout << " ---";
    }
    cout << "\n";

    for (int i = 1; i < (n + 1); i++) {
        for (int j = 1; j < (n + 1); j++) {
            if (j == 1) {
                printf("%3d  |  ", v[i]);
            }
            printf("%3d ", m[i][j]);
        }
        cout << endl;
    }
    return;
}

//Print out the graph's adjacency matrix
void printGraph(GRAPH *g) {
    cout << "     |  ";
    for (int i = 1; i < (g->vertices + 1); i++) {
        printf("%3d ", i);
    }
    cout << "\n--- -+-";
    for (int i = 1; i < (g->vertices + 1); i++) {
        cout << " ---";
    }
    cout << "\n";

    for (int i = 1; i < (g->vertices + 1); i++) {
        for (int j = 1; j < (g->vertices + 1); j++) {
            if (j == 1) {
                printf("%3d  |  ", i);
            }
            printf("%3d ", g->A[i][j]);
        }
        cout << endl;
    }
    return;
}

// deallocate memory for graph
void deleteGraph(GRAPH *g) {
    //delete arrays of arrays
    for (int i = 1; i < g->vertices + 1; i++) {
        delete[] g->A[i];
        delete[] g->vA[i];
    }

    delete[] g->A;
    delete[] g->vA;
    delete[] g->names;
    delete g;
}

void deleteVirt(GRAPH *g, int n){
    for (int i = 1; i < n + 1; i++) {
        delete[] g->virt[i];
    }
    delete[] g->virt;
}