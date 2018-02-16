#ifndef KRUSKALL_H_INCLUDED
#define KRUSKALL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
 

using namespace std;

// a structure to represent a weighted edge in graph

struct Edge

{
    int src, dest;
    double weight;
};

 

// a structure to represent a connected, undirected and weighted graph

struct Graph

{
        // V-> Number of vertices, E-> Number of edges
        int V, E;

        // graph is represented as an array of edges. Since the graph is
        // undirected, the edge from src to dest is also edge from dest
        // to src. Both are counted as 1 edge here.
        struct Edge* edge;
        int* vertex;
        // std::vector<int> verticesOfGraph;

};

 
// A structure to represent a subset for union-find
struct subset
{
        int parent;
        int rank;

};

Graph* createGraph(int V, int E);
Graph* createGraph(const std::vector<int> &vertexes, int E);
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
int myComp(const void* a, const void* b);
double KruskalMST(struct Graph* graph);


#endif