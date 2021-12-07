#include <iostream>

#include "graph.h"
#define INF 99999

/* 
This file contains more complex algorithms/functions related to the graph structure defined in graph.h
*/

//Returns graph O, the derived graph of g which has odd-degree vertices
GRAPH *locateOddVertices(GRAPH *g) {
    int *odds = new int[g->vertices + 1];
    int numOdd = 1;  //this will be the number of vertices for graph O
    for (int i = 1; i < (g->vertices + 1); i++) {
        int v = 0;  //counter for # vertices
        for (int j = 1; j < (g->vertices + 1); j++) {
            if (g->A[i][j] == 1)
                v++;
        }
        if (v % 2 == 1) {
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
    O = Initialize(numOdd - 1, oddEdges);

    for (int i = 0; i < numOdd; i++) {
        O->names[i] = odds[i];
    }
    delete[] odds;

    return O;
}

//Finds the distance of the shortest path between all pairs of vertices
//Then it applies this to the derivative graph
GRAPH *floydWarshall(GRAPH *g, GRAPH *o) {
    int V = g->vertices;
    int **dist = new int *[V + 1];
    for (int a = 1; a < (V + 1); a++) {
        dist[a] = new int[V + 1];
    }

    dist = g->A;

    //F-W algo requires a distinction between "no path" (infinity) and "points to itself" (0), something I have learned the hard way...
    for (int a = 1; a < (V + 1); a++) {
        for (int b = 1; b < (V + 1); b++) {
            if (dist[a][b] == 0)
                dist[a][b] = INF;
        }
        dist[a][a] = 0;
    }

    //actual floyd warshall algorithm
    for (int k = 1; k < (V + 1); k++) {
        for (int i = 1; i < (V + 1); i++) {
            for (int j = 1; j < (V + 1); j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    //update derived graph o
    for (int a = 1; a < (o->vertices + 1); a++) {
        for (int b = 1; b < (o->vertices + 1); b++) {
            o->A[a][b] = dist[o->names[a]][o->names[b]];
        }
    }

    //delete allocated memory
    for (int a = 1; a < (o->vertices + 1); a++) {
        delete[] dist[a];
    }
    delete[] dist;

    return o;
}

//initialize new list of edges, where n = maximum number of edges
PATH * initializePath(int n) {
    PATH *p = new PATH;
    p->quant = 0;            //current number of edges in the "path"
    p->P = new EDGE[n + 1];  //unsorted set of edges from o. This array starts from 1 just to be consistent with the other arrays of this program.
    for (int i = 1; i < (n + 1); i++) {
        p->P[i].a = -1;
        p->P[i].b = -1;
        p->P[i].weight = -1;
    }
    return p;
}

//delete allocated memory for a PATH variable
void deletePath(PATH *p) {
    delete[] p->P;
    delete p;
}

//add EDGE(u,v) w/ W to PATH p
PATH *appendPath(PATH *p, int u, int v, int W) {
    p->quant++;
    p->P[p->quant].a = u;
    p->P[p->quant].b = v;
    p->P[p->quant].weight = W;
    return p;
}

//print path in the matching style
void printPath(PATH *p){
    int n = p->quant;
    cout << "{";
    for (int i = 1; i < n+1; i++)
    {
        cout << " (";
        cout << p->P[i].a;
        cout << ",";
        cout << p->P[i].b;
        cout << ") ";
    }
    cout << "}";
    
}

//returns TRUE if Vertex v is incident with any edges in PATH p
//remember to pass v as vertex name 
bool incidentPath(int v, PATH* p){
    if(p->quant)
    for (int i = 1; i < (p->quant + 1); i++) {
        if(v == p->P[i].a || v == p->P[i].b){
            return true;
        }   
    }
    return false;
}

//Apply insertion sort to path
PATH* insertionSort(PATH *path)
{
    int n = path->quant;
    int i, j; //markers
    EDGE key;
    for (i = 2; i < n+1; i++)
    {
        key = path->P[i];
        j = i - 1;
 
        /* Move elements of path->P[0..i-1].weight, that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 1 && path->P[j].weight > key.weight)
        {
            path->P[j + 1] = path->P[j];
            j = j - 1;
        }
        path->P[j + 1] = key;
    }
    return path;
}

//return a set of EDGEs that form a perfect matching for argument graph
PATH *perfectMatching(GRAPH *o) {
    PATH *u = initializePath(o->edges);  //unsorted PATH
    PATH *m = initializePath(o->edges);  //perfect matching PATH

    //add existing edges to path U
    for (int x = 1; x < o->vertices + 1; x++) {
        for (int y = 1; y < o->vertices + 1; y++) {
            if (o->A[x][y] != 0) {  //if the edge exists
                u = appendPath(u, o->names[x], o->names[y], o->A[x][y]);
            }
        }
    } 
    //sort the path
    u = insertionSort(u);
    /* 
    Iterate through u; add edge(u,v) to perfect matching M if it is NOT incident
    with any of the edges already existing in M 
    */
    for (int i = 1; i < u->quant + 1; i++)
    {
        int a = u->P[i].a;
        int b = u->P[i].b;
        int weight = u->P[i].weight;
        if(m->quant == 0){
            m = appendPath(m, a, b, weight);
        } else if(!incidentPath(a, m) && !incidentPath(b, m)){
            m = appendPath(m, a, b, weight);
        }
    }
    
    return m;
}//end of perfect matching

// GRAPH *insertVirtuals(MATCH *m){

// }

// void euler(GRAPH *g){

// }