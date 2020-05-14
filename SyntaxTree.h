/*********************************************
*
*           Andre Leite - 2015250489
*           Lucas Ferreira - 2016243439
*
**********************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node *pointer;
typedef struct stack *stack_p;

typedef struct stack{
	pointer node;
	stack_p next;
}Stack;

typedef struct node{

	int column;
	int line;

	char *type;
	char *id;

	char *id_type;
	char param_t[32][32];
	int card_p_t;

	pointer sibling;
	pointer child;
	pointer ptr;

}Node;

Node* initNode(char* type, char* id, int line, int col);
void addChild(Node *node, Node *child);
void addSibling(Node *node, Node *sibling);
void arrangeCol(Node *node, Node *n);
void printThemTrees(Node *root,int dottydots);
void destroyThemTrees(Node *root);
int checkBlock(Node *head);