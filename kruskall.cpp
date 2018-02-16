#include "kruskall.h"
// Creates a graph with V vertices and E edges

struct Graph* createGraph(int V, int E)

{

    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    
    graph->V = V;
    graph->E = E;

    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    graph->vertex = (int*) malloc(graph->V * sizeof(int));
    for (int i=0;i<graph->V;i++) graph->vertex[i]=i;
    return graph;

}

 
struct Graph* createGraph(const std::vector<int> &vertexes, int E)

{

    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    
    graph->V = vertexes.size();
    graph->E = E;

    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    graph->vertex = (int*) malloc(graph->V * sizeof(int));
    for (int i=0;i<graph->V;i++) graph->vertex[i]=vertexes[i];
    return graph;

}
 

// // A utility function to find set of an element i
// (uses path compression technique)
// in fact this is the representant of the set, the root of the trre associated with the subset

int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
//in this function it is worth to notice that i is the id of the node, that represents also an image

    return subsets[i].parent;
}

 

// A function that does union of two sets of x and y (if they belong to two differents trees)

// // (uses union by rank)

void Union(struct subset subsets[], int x, int y)

{

    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high rank tree

    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

 

    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }

}

 

// Compare two edges according to their weights.

// Used in qsort() for sorting an array of edges

int myComp(const void* a, const void* b)

{

    struct Edge* a1 = (struct Edge*) a;

    struct Edge* b1 = (struct Edge*) b;

    return (int) a1->weight-b1->weight;

}

 

// The main function to construct MST using Kruskal's algorithm

double KruskalMST(struct Graph* graph)

{

    int V = graph->V;

    struct Edge result[V]; // Tnis will store the resultant MST

    int e = 0; // An index variable, used for result[]

    int i = 0; // An index variable, used for sorted edges

    // Step 1:  Sort all the edges in non-decreasing order of their weight

    // If we are not allowed to change the given graph, we can create a copy of

    // array of edges

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
    // Allocate memory for creating V ssubsets

    struct subset *subsets = (struct subset*) malloc(V * sizeof(struct subset));
    // Create V subsets with single elements

    for (int v = 0; v < V; ++v)
    {
        subsets[graph->vertex[v]].parent = graph->vertex[v];
        subsets[graph->vertex[v]].rank = 0;
    }

 

    // Number of edges to be taken is equal to V-1

    while (e < V - 1)

    {

        // Step 2: Pick the smallest edge. And increment the index

        // for next iteration

        struct Edge next_edge = graph->edge[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does't cause cycle, include it

        // in result and increment the index of result for next edge

        if (x != y)// it means here that there is no cycle
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }

        // Else discard the next_edge

    }



    double cost=0;
    // print the contents of result[] to display the built MST

    // cout<<"Following are the edges in the constructed MST\n";

    for (i = 0; i < e; ++i)
    	{
        // printf("%d -- %d == %4.2f\n", result[i].src, result[i].dest,result[i].weight);
    	cost+=result[i].weight;
    	}
    return cost;

}