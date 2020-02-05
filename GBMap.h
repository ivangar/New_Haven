#ifndef GBMAP_H_INCLUDED
#define GBMAP_H_INCLUDED


typedef struct n LLNode;

struct n
{
	int data;
	LLNode *next;
};

typedef struct graph Graph;

struct graph
{
	int nv;
	int ne;
	LLNode** adjList;
};

LLNode *createLLNode(int data);
LLNode *insertInBegin(LLNode *h, int data);
void traverse(LLNode *h);
LLNode *findLastNode(LLNode *h);
LLNode *insertInEnd(LLNode *h, int data);
LLNode *deleteNodeWithValue(LLNode *h, int data);
LLNode *createSerialList(int s, int e);
int countLinkedListNodes(LLNode *h);
LLNode *searchNodeWithValue(LLNode *h, int data);

Graph *createGraph(int nv);
void insertEdge(Graph *g, int u, int v);
//void deleteEdge(Graph *g, int u, int v);
Graph *destroyGraph(Graph *g);

void printGraph(Graph *g);

#endif