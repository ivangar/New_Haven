#include "llnode.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

LLNode *createLLNode(int data)
{
	LLNode *t = (LLNode *)malloc(sizeof(LLNode));

	t->data = data;
	t->next = NULL;

	return t;
}

LLNode *insertInBegin(LLNode *h, int data)
{
	LLNode *t = createLLNode(data);

	t->next = h;
	return t;
}

void traverse(LLNode *h){

	LLNode *c = h;

	while( c != NULL){
		printf("%d ", c->data );
		c = c->next;
	}
}


LLNode *findLastNode(LLNode *h)
{
	while( h->next != NULL){
		h = h->next;
	}

	return h;
}

LLNode *insertInEnd(LLNode *h, int data)
{
	LLNode *t = createLLNode(data);

	if(h == NULL)
		return t;
	LLNode *l = findLastNode(h);

	l->next = t;

	return h;
}