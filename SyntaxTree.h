/*********************************************
*
*           Andre Leite - 2015250489
*
**********************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node{
	char *type;
	char *id;
	struct node *sibling;
	struct node *child;
	struct node *ptr;
}Node;

Node* initNode(char* type, char* id);
void addChild(Node *node, Node *child);
void addSibling(Node *node, Node *sibling);
void printThemTrees(Node *root,int dottydots);
void destroyThemTrees(Node *root);
int checkBlock(Node *head);