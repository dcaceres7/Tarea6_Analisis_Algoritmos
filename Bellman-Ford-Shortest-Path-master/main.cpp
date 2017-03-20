#include "Test.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
using namespace std;
struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph =
         (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;

    graph->edge =
       (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

    return graph;
}

int* BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
    int *res = new int[V];

    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX;
        res[i] = NULL;
    }
    dist[src] = 0;

    for (int i = 1; i <= V-1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
                res[v]=u;
            }
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            printf("Graph contains negative weight cycle");
    }
    return res;
}

int getSizeVertices(int** graph, int size){
    int cont = 0;
     for(int i = 0 ; i<size; i++){
        for(int j = 1 ; j<size; j++){
            if(graph[i][j]!=-1)
                cont +=1;
        }
    }
    return cont;
}

int* getShortestPath(int** graph, int size, int origin)
{
    int E =getSizeVertices(graph, size);
    struct Graph* graphs = createGraph(size, E);
    int cont=0;
    for(int i = 0 ; i<size; i++){
        for(int j = 1 ; j<size; j++)
            if(graph[i][j]!=-1){
                graphs->edge[cont].src = i;
                graphs->edge[cont].dest = j;
                graphs->edge[cont].weight = graph[i][j];
                cont +=1;
            }
    }
    return BellmanFord(graphs, 0);
}

int main ()
{
    test();
    return 0;
}
