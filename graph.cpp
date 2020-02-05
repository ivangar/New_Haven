#include "graph.h"
#include "llnode.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

Graph *createGraph(int nv)
{
	Graph *g = (Graph *)malloc(sizeof(Graph));
	g->nv = nv;
	g->ne = 0;
	g->adjList = (LLNode **)malloc(nv * sizeof(LLNode *));

	int i;
	for(i=0;i<nv;i++)
	{
		g->adjList[i] = NULL;
	}
	return g;
}
void insertEdge(Graph *g, int u, int v)
{
	assert(g != NULL);
	g->adjList[u] = insertInBegin(g->adjList[u], v);
	g->adjList[v] = insertInBegin(g->adjList[v], u);
	g->ne++;
}

/*
void deleteEdge(Graph *g, int u, int v)
{
	assert(g != NULL);
	g->adjList[u] = deleteNodeWithValue(g->adjList[u], v);
	g->adjList[v] = deleteNodeWithValue(g->adjList[v], u);
	g->ne--;
}
*/

Graph *destroyGraph(Graph *g);

void printGraph(Graph *g)
{
	int i;
	for(i=0;i < g->nv; i++)
	{
		printf("%d : ", i);
		traverse(g->adjList[i]);
		printf("\n");
	}
}
