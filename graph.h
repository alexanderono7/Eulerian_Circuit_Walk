struct GRAPH
{
    int vertices;
    int edges;
    int **A; //2 dimensional graph is used to show edge relationships, size is (vertices)x(vertices).
    //A stands for Adjacency Matrix
    /*A should be initialized to 0 before its edge relationships
    are assigned.*/
};

GRAPH *graphInput(GRAPH *graph);
GRAPH *Initialize(int n, int m);
GRAPH *assignEdge(GRAPH *g, int u, int v, int weight);
void printGraph(GRAPH *g);
void deleteGraph(GRAPH *g);

