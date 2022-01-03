//created by Alexander Ono
#include <iostream>

#include "graph.h"
#include "graphUtil.h"

//returns true if vertex v still has any edges remaining, including virtual edges
bool hasAnyEdges(int v, GRAPH* g) {
    //normal edges checked first
    for (int i = 1; i < (g->vertices + 1); i++) {
        if (g->A[v][i] != 0 || g->vA[v][i] != 0) {
            return true;
        }
    }
    return false;
}

//formation of the circuit
PATH* euler(GRAPH* g, PATH* circuit) {
    PATH* stack;
    stack = initializePath(g->vertices * g->vertices);
    int u, current, v;
    EDGE e;
    current = 1;
    
    //terminate when current node has 0 edges left AND stack is empty
    while (hasAnyEdges(current, g) || stack->quant != 0) {
        
            u = current;
            v = 1;
            while (v < (g->vertices + 1)) {

                //a real edge exists condition
                if (g->A[u][v] != 0) {
                    stack = append(stack, u, v, 1);
                    g->A[u][v] = 0;
                    g->A[v][u] = 0;
                    u = v;
                    v = 0;
                    //a virtual edge exists condition
                } else if (g->vA[u][v] != 0) {
                    int weight = g->vA[u][v];
                    stack = append(stack, u, v, weight);
                    g->vA[u][v] = 0;
                    g->vA[v][u] = 0;
                    g->A[u][v] = 0;
                    g->A[v][u] = 0;
                    u = v;
                    v = 0;
                } else {
                }
                v++;
            }
        
        //pop the stack
        e = stack->P[stack->quant];
        stack = pop(stack);
        // circuit = recoverPath(g, circuit, 3, 5);
        //append edge to circuit
        if (e.weight != 1) {
            circuit = recoverPath(g, circuit, e.b, e.a);

        } else {
            circuit = append(circuit, e.b, e.a, 1);
        }
        current = e.a;
    }
    deletePath(stack);
    return circuit;
}

void printCircuit(PATH *p) {
    int n = p->quant;
    for (int i = 1; i < n + 1; i++) {
        cout << "\n          (";
        cout << p->P[i].a;
        cout << ",";
        cout << p->P[i].b;
        cout << ") ";
    }
}
