//created by Alexander Ono
#include <iostream>

#include "graph.h"
#define INF 99999

/* 
This file contains more complex algorithms/functions related to the graph structure defined in graph.h
*/

//initialize virtual subarray of graph - needs to be done separately from graph initialization due to potential difference in sizes
GRAPH *initializeVirtuals(GRAPH *g, int n) {
    g->virt = new int *[n + 1];
    for (int i = 1; i < (n + 1); i++) {
        g->virt[i] = new int[n + 1];
    }
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            g->virt[i][j] = 0;
        }
    }
    return g;
}

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

    for (int a = 1; a < (V + 1); a++) {
        for (int b = 1; b < (V + 1); b++) {
            dist[a][b] = g->A[a][b];
        }
    }

    //F-W algo requires a distinction between "no path" (infinity) and "points to itself" (0), something I have learned the hard way...
    //set all nodes besides self-paths to "infinity"
    for (int a = 1; a < (V + 1); a++) {
        for (int b = 1; b < (V + 1); b++) {
            if (dist[a][b] == 0 && a != b)
                dist[a][b] = INF;

            if (dist[a][b] != 0) {
                o->virt[a][b] = b;
            }
        }
        o->virt[a][a] = a;
    }

    //actual floyd warshall algorithm
    for (int k = 1; k < (V + 1); k++) {
        for (int i = 1; i < (V + 1); i++) {
            for (int j = 1; j < (V + 1); j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    o->virt[i][j] = o->virt[i][k];  //track paths of future virtual edges
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
PATH *initializePath(int n) {
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
PATH *append(PATH *p, int u, int v, int W) {
    p->quant++;
    p->P[p->quant].a = u;
    p->P[p->quant].b = v;
    p->P[p->quant].weight = W;
    return p;
}

PATH *pop(PATH *p) {
    p->P[p->quant].a = 0;
    p->P[p->quant].b = 0;
    p->P[p->quant].weight = 0;
    p->quant--;
    return p;
}

PATH *recoverPath(GRAPH *g, PATH *p, int u, int v) {
    if (g->virt[u][v] == 0) cout << "ERROR";
    int last = u;
    while (u != v) {
        u = g->virt[u][v];
        p = append(p, last, u, 1);
        last = u;
    }
    return p;
}

//print path in the matching style
void printPath(PATH *p) {
    int n = p->quant;
    cout << "{";
    for (int i = 1; i < n + 1; i++) {
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
bool incidentPath(int v, PATH *p) {
    if (p->quant)
        for (int i = 1; i < (p->quant + 1); i++) {
            if (v == p->P[i].a || v == p->P[i].b) {
                return true;
            }
        }
    return false;
}

//Apply insertion sort to path
PATH *insertionSort(PATH *path) {
    int n = path->quant;
    int i, j;  //markers
    EDGE key;
    for (i = 2; i < n + 1; i++) {
        key = path->P[i];
        j = i - 1;

        /* Move elements of path->P[0..i-1].weight, that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 1 && path->P[j].weight > key.weight) {
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
                u = append(u, o->names[x], o->names[y], o->A[x][y]);
            }
        }
    }
    //sort the path
    u = insertionSort(u);
    /* 
    Iterate through u; add edge(u,v) to perfect matching M if it is NOT incident
    with any of the edges already existing in M 
    */
    for (int i = 1; i < u->quant + 1; i++) {
        int a = u->P[i].a;
        int b = u->P[i].b;
        int weight = u->P[i].weight;
        if (m->quant == 0) {
            m = append(m, a, b, weight);
        } else if (!incidentPath(a, m) && !incidentPath(b, m)) {
            m = append(m, a, b, weight);
        }
    }

    return m;
}  //end of perfect matching

//Insert edges from path m into graph g
GRAPH *insertVirtuals(PATH *m, GRAPH *g) {
    for (int i = 1; i < m->quant + 1; i++) {
        int u = m->P[i].a;
        int v = m->P[i].b;
        int w = m->P[i].weight;

        g->vA[u][v] = w;
        g->vA[v][u] = w;
    }

    return g;
}
