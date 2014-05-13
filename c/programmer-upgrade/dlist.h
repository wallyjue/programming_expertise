
#ifndef __IF_DLIST_H__
#define __IF_DLIST_H__

typedef struct _Node Node;
struct _Node
{
	int index;
	int number;
	char* content;
	int content_len;
	Node *prevnode;
	Node *nextnode;
};

typedef struct _NodeList NodeList;
struct _NodeList{
	Node* headnode;
	Node* tailnode;
};

typedef void (*DListVisitNode) (Node*, void*);
void DListTraverse( NodeList* , DListVisitNode , void*);

void FindMax( Node* node, void* ctx);
int DListAddNode( NodeList* nodelist, Node* node);
Node* InitNode(int index, char* content);
void FreeNode( Node* node);


void print_index( Node* node, void* ctx);
void print_content( Node* node, void* ctx);
void content_to_upper(Node* node, void* ctx);
void SumIndex(Node* node, void* ctx);
void FindMax( Node* node, void* ctx);


#define RET_OK 1
#define RET_FAIL 0

#endif
