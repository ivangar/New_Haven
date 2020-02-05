#include <iostream>
#include <cstdio>
#include "GBMap.h"

using namespace std;

int main()
{
	/*
	Graph *g = createGraph(6);

	insertEdge(g, 0, 4);
	insertEdge(g, 0, 3);
	insertEdge(g, 1, 3);
	insertEdge(g, 1, 5);
	insertEdge(g, 2, 4);
	insertEdge(g, 4, 5);
*/
	Graph *g = createGraph(8);

	insertEdge(g, 0, 2);
	insertEdge(g, 3, 2);
	insertEdge(g, 4, 2);
	insertEdge(g, 1, 2);
	insertEdge(g, 1, 5);
	insertEdge(g, 5, 6);
	insertEdge(g, 5, 7);

	printGraph(g);

	return 0;

}