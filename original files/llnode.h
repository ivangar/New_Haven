#ifndef LLNODE_H_INCLUDED
#define LLNODE_H_INCLUDED


typedef struct n LLNode;

struct n
{
	int data;
	LLNode *next;
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

#endif