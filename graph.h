#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "llnode.h"

typedef struct graph Graph;

struct graph
{
	int nv;
	int ne;
	LLNode** adjList;
};

Graph *createGraph(int nv);
void insertEdge(Graph *g, int u, int v);
//void deleteEdge(Graph *g, int u, int v);
Graph *destroyGraph(Graph *g);

void printGraph(Graph *g);


#endif